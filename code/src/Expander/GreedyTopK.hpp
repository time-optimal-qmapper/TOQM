#ifndef GREEDYTOPKEXPANDER_HPP
#define GREEDYTOPKEXPANDER_HPP

#include <cassert>
#include <vector>
#include <iostream>
#include <queue>
#include "Expander.hpp"
#include "Queue.hpp"
#include "CostFunc.hpp"

class GreedyTopK : public Expander {
  private:
	unsigned int K = 0;
	struct CmpNodeCost
	{
		//REMINDER: I reversed the cost function here so I could remove inferior nodes on the fly, maintaining a smaller priority queue of only K nodes
		bool operator()(const Node* lhs, const Node* rhs) const
		{
			//tiebreaker:
			if(lhs->cost == rhs->cost) {
				return lhs->cost2 <= rhs->cost2;
			}
			
			//lower cost is better
			return lhs->cost < rhs->cost;
		}
	};
  public:
	int setArgs(char** argv) {
		K = atoi(argv[0]);
		return 1;
	}
	
	int setArgs() {
		std::cerr << "Enter value of K for top-k expander: K=";
		std::cin >> K;
		return 1;
	}
	
	bool expand(Queue * nodes, Node * node) {
		//return false if we're done expanding
		if(nodes->getBestFinalNode() && node->cost >= nodes->getBestFinalNode()->cost) {
			return false;
		}
		
		//assert(this->K > 0);
		
		unsigned int nodesSize = nodes->size();
		int numQubits = node->env->numPhysicalQubits;
		
		bool occupied[numQubits];
		bool onReadyFrontier[numQubits];
		bool hasBusyQubits = false;
		for(int x = 0; x < numQubits; x++) {
			occupied[x] = false;
			onReadyFrontier[x] = false;
			if(node->busyCycles(x) > 0) {
				hasBusyQubits = true;
			}
		}
		
		//Identify, for each logical qubit, the CX (if any) that's on the CX frontier
		GateNode * CXFrontier[numQubits];
		for(int x = 0; x < numQubits; x++) {
			CXFrontier[x] = NULL;
		}
		for(auto iter = node->readyGates.begin(); iter != node->readyGates.end(); iter++) {
			GateNode * g = *iter;
			if(g->control >= 0) {
				CXFrontier[g->target] = g;
				CXFrontier[g->control] = g;
				//std::cerr << " ready frontier CX: L" << g->target << ",L" << g->control << "\n";
			}
		}
		for(auto iter = node->readyGates.begin(); iter != node->readyGates.end(); iter++) {
			GateNode * g = *iter;
			if(g->control < 0) {
				g = g->nextTargetCNOT;
				if(g) {
					if(!CXFrontier[g->control]) {
						CXFrontier[g->target] = g;
						CXFrontier[g->control] = g;
						//std::cerr << " ready frontier CX: L" << g->target << ",L" << g->control << "\n";
					} else if(CXFrontier[g->control]->criticality < g->criticality) {
						//std::cerr << "sanity check fail gtk~112\n";
						CXFrontier[CXFrontier[g->control]->target] = NULL;
						CXFrontier[g->target] = g;
						CXFrontier[g->control] = g;
						//std::cerr << " ready frontier CX: L" << g->target << ",L" << g->control << "\n";
					}
				}
			}
		}
		
		//generate list of valid gates, based on ready list and list of possible swaps
		vector<GateNode*> possibleGates;
		vector<GateNode*> guaranteedGates;
		for(auto iter = node->readyGates.begin(); iter != node->readyGates.end(); iter++) {
			GateNode * g = *iter;
			int target = (g->target < 0) ? -1 : node->laq[g->target];
			int control = (g->control < 0) ? -1 : node->laq[g->control];
			
			bool good = (node->cycle >= -1);
			//bool dependsOnSomething = false;
			
			if(control >= 0) {//gate has a control qubit
				onReadyFrontier[control] = true;
				int busy = node->busyCycles(control);
				if(busy) {
					//dependsOnSomething = true;
					if(busy > 1) {
						good = false;
					}
				}
			}
			
			if(target >= 0) {//gate has a target qubit
				onReadyFrontier[target] = true;
				int busy = node->busyCycles(target);
				if(busy) {
					//dependsOnSomething = true;
					if(busy > 1) {
						good = false;
					}
				}
			}
			
			if(good && control >= 0 && target >= 0) {//gate has 2 qubits
				if(node->env->couplings.count(make_pair(target,control)) <= 0) {
					if(node->env->couplings.count(make_pair(control,target)) <= 0) {
						good = false;
					}
				}
			}
			
			if(good) {
				guaranteedGates.push_back(g);
				occupied[target] = true;
				if(control >= 0) {
					occupied[control] = true;
				}
			}
		}
		for(unsigned int x = 0; x < node->env->couplings.size(); x++) {
			GateNode * g = node->env->possibleSwaps[x];
			int target = g->target;//note: since g is swap, this is already the physical target
			int control = g->control;//note: since g is swap, this is already the physical control
			int logicalTarget = (target >= 0) ? node->qal[target] : -1;
			int logicalControl = (control >= 0) ? node->qal[control] : -1;
			
			bool what = false;
			//if(node->numUnscheduledGates==18444 && control == 10 && target == 11) {
			//	what = true;
			//}
			
			bool helpsCX = false;
			bool hurtsExecutableCX = false;
			if(logicalTarget >= 0 && CXFrontier[logicalTarget]) {
				GateNode * cx = CXFrontier[logicalTarget];
				assert(cx->target >= 0);
				assert(cx->control >= 0);
				if(node->laq[cx->control] >= 0 && node->laq[cx->target] >= 0) {
					int currentDist = node->env->couplingDistances[node->laq[cx->control]*node->env->numPhysicalQubits + node->laq[cx->target]];
					assert(node->swapQubits(target, control));
					int hypotheticDist = node->env->couplingDistances[node->laq[cx->control]*node->env->numPhysicalQubits + node->laq[cx->target]];
					assert(node->swapQubits(target, control));
					
					//std::cerr << " swapT (" << cx->control << "," << cx->target <<") L" << logicalTarget << ",L" << logicalControl << " P" << target << ",P" << control << " : ";
					//std::cerr << currentDist << " vs " << hypotheticDist << " : ";
					if(hypotheticDist < currentDist) {
						helpsCX = true;
						//std::cerr << "helps L" << logicalTarget << ". ";
					} else if (hypotheticDist > currentDist && currentDist == 1) {
						hurtsExecutableCX = true;
					}
					//std::cerr << "\n";
				}
			}
			if(logicalControl >= 0 && CXFrontier[logicalControl]) {
				GateNode * cx = CXFrontier[logicalControl];
				assert(cx->target >= 0);
				assert(cx->control >= 0);
				if(node->laq[cx->control] >= 0 && node->laq[cx->target] >= 0) {
					int currentDist = node->env->couplingDistances[node->laq[cx->control]*node->env->numPhysicalQubits + node->laq[cx->target]];
					assert(node->swapQubits(target, control));
					int hypotheticDist = node->env->couplingDistances[node->laq[cx->control]*node->env->numPhysicalQubits + node->laq[cx->target]];
					assert(node->swapQubits(target, control));
					
					//std::cerr << " swapC (" << cx->control << "," << cx->target <<") L" << logicalTarget << ",L" << logicalControl << " P" << target << ",P" << control << " : ";
					//std::cerr << currentDist << " vs " << hypotheticDist << " : ";
					if(hypotheticDist < currentDist) {
						helpsCX = true;
						//std::cerr << "helps L" << logicalControl << ". ";
					} else if (hypotheticDist > currentDist && currentDist == 1) {
						hurtsExecutableCX = true;
					}
					//std::cerr << "\n";
				}
			}
			
			bool good = (node->cycle < -1 || (!occupied[target] && !occupied[control])) && (helpsCX);// && !hurtsExecutableCX);
			if(what) std::cerr << " good init: " << good << "\n";
			bool dependsOnSomething = false;
			
			bool usesLogicalQubit = false;
			if(good && logicalTarget >= 0) {
				usesLogicalQubit = true;
			}
			if(good && logicalControl >= 0) {
				usesLogicalQubit = true;
			}
			good = good && usesLogicalQubit;
			
			if(what && !usesLogicalQubit) std::cerr << " doesn't use any valid logical bit\n";
			
			bool usesUsefulLogicalQubit = false;
			if(good) {
				if(logicalTarget >= 0) {
					ScheduledGate * t = node->lastNonSwapGate[logicalTarget];
					if(t) {
						GateNode * tg = t->gate;
						if(tg->target == logicalTarget) {
							if(tg->targetChild) {
								usesUsefulLogicalQubit = true;
							}
						} else {
							assert(tg->control == logicalTarget);
							if(tg->controlChild) {
								usesUsefulLogicalQubit = true;
							}
						}
					} else {
						usesUsefulLogicalQubit = true;//better safe than sorry
					}
				}
				
				if(logicalControl >= 0) {
					ScheduledGate * c = node->lastNonSwapGate[logicalControl];
					if(c) {
						GateNode * cg = c->gate;
						if(cg->target == logicalControl) {
							if(cg->targetChild) {
								usesUsefulLogicalQubit = true;
							}
						} else {
							assert(cg->control == logicalControl);
							if(cg->controlChild) {
								usesUsefulLogicalQubit = true;
							}
						}
					} else {
						usesUsefulLogicalQubit = true;//better safe than sorry
					}
				}
			}
			if(!usesUsefulLogicalQubit) {//swapping qubits that are never used again
				good = false;
				if(what) std::cerr << " doesn't use useful bit\n";
			}
			
			int busyT = node->busyCycles(target);
			if(good && busyT) {
				dependsOnSomething = true;
				if(busyT > 1) {
					good = false;
					if(what) std::cerr << " busy control\n";
				}
			}
			int busyC = node->busyCycles(control);
			if(good && busyC) {
				dependsOnSomething = true;
				if(busyC > 1) {
					good = false;
					if(what) std::cerr << " busy target\n";
				}
			}
			if(good && nodesSize > 0 && !dependsOnSomething && !onReadyFrontier[target] && !onReadyFrontier[control]) {
				//good = false;
				//if(what) std::cerr << " dependence fail\n";
			}
			if(good) {
				if(what) std::cerr << " IS GOOD!\n";
				possibleGates.push_back(g);
			}
		}
		
		std::priority_queue<Node*, std::vector<Node*>, CmpNodeCost> tempNodes;
		
		assert(possibleGates.size() < 64); //or else I need to do this differently
		unsigned long long numIters = 1LL << possibleGates.size();
		
		for(unsigned long long x = 0; x < numIters; x++) {
			//ToDo: investigate case where this if-statement evaluates to true:
			//if(node->parent && node->parent->dead) {
				//node->dead = true;
				//break;
			//}
			
			Node * child = node->prepChild();
			bool good = true;
			//schedule different subset of swaps and 2-qubit gates than for previous child nodes
			for(unsigned int y = 0; good && y < possibleGates.size(); y++) {
				if(x & (1LL << y)) {
					if(node->cycle >= -1) {
						good = good && child->scheduleGate(possibleGates[y]);
					} else {
						good = good && child->swapQubits(possibleGates[y]->target, possibleGates[y]->control);
					}
				}
			}
			
			if(x == 0) {
				if(guaranteedGates.size() == 0 && !hasBusyQubits) {
					continue;
				}
			}
			
			if(!good) {
				delete child;
			} else {
				//schedule as many of the 1-cycle ready gates as we can:
				for(unsigned int y = 0; good && y < guaranteedGates.size(); y++) {
					good = child->scheduleGate(guaranteedGates[y]);
					assert(good);
				}
				
				child->cost = node->env->cost->getCost(child);
				/*if(what || (x==0 && node->numUnscheduledGates==18444)) {
					if(what) std::cerr << "swap:\n";
					else std::cerr << "nada:\n";
					int garbage = node->env->cost->getCost(child);
					std::cerr << "COST: " << garbage << "\n";
					if(what) cin >> garbage;
				}*/
				
				//if(!this->K || this->K >= numIters) {
				//	if(!nodes->push(child)) {
				//		delete child;
				//	}
				//} else {
					tempNodes.push(child);
					
					//If priority queue is overfilled, delete extra node:
					if(tempNodes.size() > this->K) {
						Node * worstNode = tempNodes.top();
						tempNodes.pop();
						delete worstNode;
					}
					assert(tempNodes.size() <= this->K);
				//}
			}
		}
		
		//if(this->K && this->K < numIters) {
			//Push top K into main priority queue
			int counter = this->K;
			while(counter > 0 && tempNodes.size() > 0) {
				Node * child = tempNodes.top();
				tempNodes.pop();
				if(nodes->push(child)) {
					counter--;
				} else {
					std::cerr << "SANITY CHECK ERROR: i guess not all pushed nodes will go through for top-k after all; therefore I need to redo the optimization handling the overfill\n";
					delete child;
				}
			}
			
			//cleanup the discarded children
			while(tempNodes.size() > 0) {
				Node * child = tempNodes.top();
				tempNodes.pop();
				delete child;
			}
		//}
		
		return true;
	}
};

#endif
