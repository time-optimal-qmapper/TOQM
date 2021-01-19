#ifndef DEFAULTEXPANDER_HPP
#define DEFAULTEXPANDER_HPP

#include <cassert>
#include <vector>
#include <iostream>
#include "Expander.hpp"
#include "Queue.hpp"
#include "CostFunc.hpp"

void printNodeEx(std::ostream & stream, LinkedStack<ScheduledGate*> * gates) {
	if(gates->size == 0) {
		return;
	}
	printNodeEx(stream, gates->next);
	
	ScheduledGate * sg = gates->value;
	int target = sg->physicalTarget;
	int control = sg->physicalControl;
	//stream << "\t";
	stream << sg->gate->name << " ";
	if(control >= 0) {
		stream << "q[" << control << "],";
	}
	stream << "q[" << target << "]";
	stream << ";";
	stream << " //cycle: " << sg->cycle;
	if(sg->gate->name.compare("swp") && sg->gate->name.compare("SWP")) {
		int target = sg->gate->target;
		int control = sg->gate->control;
		stream << " //" << sg->gate->name << " ";
		if(control >= 0) {
			stream << "q[" << control << "],";
		}
		stream << "q[" << target << "]";
		//stream << " //criticality ";
		//stream << sg->gate->criticality;
	}
	stream << "\n";
}

//return true iff inserting swap g in node's child would make a strictly non-optimal swap cycle
bool isCyclic(Node * node, GateNode * g) {
	int target = g->target;
	int control = g->control;
	
	if(node->lastGate[target] && node->lastGate[control]) {
		LinkedStack<ScheduledGate*> * schdule = node->scheduled;
		while(schdule->size > 0) {
			if(schdule->value->gate == g) {
				return true;
			} else {
				int c = schdule->value->physicalControl;
				int t = schdule->value->physicalTarget;
				if(c >= 0) {
					if(c == control || c == target || t == control || t == target) {
						return false;
					}
				}
			}
			schdule = schdule->next;
		}
	}
	return false;
	
	//Note: code doesn't reach this point. The code below is the previous implementation of this function, which failed to detect cyclic swaps if there were any 1-qubit gates in-between
	if(node->lastGate[target] == node->lastGate[control]) {
		if(node->lastGate[target] && node->lastGate[target]->gate == g) {
			return true;
		}
	}
	return false;
}

class DefaultExpander : public Expander {
  public:
	bool expand(Queue * nodes, Node * node) {
		//return false if we're done expanding
		if(nodes->getBestFinalNode() && node->cost >= nodes->getBestFinalNode()->cost) {
			return false;
		}
		
		unsigned int nodesSize = nodes->size();
		
		bool noMoreCX[node->env->numPhysicalQubits];
		for(int x = 0; x < node->env->numPhysicalQubits; x++) {
			noMoreCX[x] = false;
			ScheduledGate * sg = node->lastNonSwapGate[x];
			if(sg) {
				if(sg->gate->target == x) {
					if(!sg->gate->nextTargetCNOT) {
						noMoreCX[x] = true;
					}
				} else {
					assert(sg->gate->control == x);
					if(!sg->gate->nextControlCNOT) {
						noMoreCX[x] = true;
					}
				}
			}
		}
		
		//generate list of valid gates, based on ready list
		vector<GateNode*> possibleGates;//possible swaps and valid 2+ cycle gates
		vector<GateNode*> singleCycleGates;//valid 1 cycle non-swap gates
		int numDependentGates = 0;
		for(auto iter = node->readyGates.begin(); iter != node->readyGates.end(); iter++) {
			GateNode * g = *iter;
			int target = (g->target < 0) ? -1 : node->laq[g->target];
			int control = (g->control < 0) ? -1 : node->laq[g->control];
			
			//assertions to double-check I'm correctly handling cases with more physical than logical qubits
			//assert(g->target < 0 || target >= 0);
			//assert(g->control < 0 || control >= 0);
			
			bool good = node->cycle >= -1;
			bool dependsOnSomething = false;
			
			if(control >= 0) {//gate has a control qubit
				int busy = node->busyCycles(control);
				if(busy) {
					dependsOnSomething = true;
					if(busy > 1) {
						good = false;
					}
				}
			} else {
				if(!g->nextTargetCNOT) {
					noMoreCX[target] = true;
				}
			}
			
			if(g->target >= 0) {//gate has a target qubit
				int busy = node->busyCycles(target);
				if(busy) {
					dependsOnSomething = true;
					if(busy > 1) {
						good = false;
					}
				}
			}
			
			if(dependsOnSomething) {
				numDependentGates++;
			}
			
			if(good && node->cycle > 0 && nodesSize > 0 && !dependsOnSomething) {
				good = false;
			}
			
			if(good && control >= 0 && target >= 0) {//gate has 2 qubits
				if(node->env->couplings.count(make_pair(target,control)) <= 0) {
					if(node->env->couplings.count(make_pair(control,target)) <= 0) {
						good = false;
					}
				}
			}
			
			if(good) {
				if(g->latency == 1) {
					singleCycleGates.push_back(g);
				} else {
					possibleGates.push_back(g);
				}
			}
		}
		//generate list of valid gates, based on possible swaps
		for(unsigned int x = 0; x < node->env->couplings.size(); x++) {
			GateNode * g = node->env->possibleSwaps[x];
			int target = g->target;//note: since g is swap, this is already a physical target
			int control = g->control;//note: since g is swap, this is already a physical control
			int logicalTarget = (target >= 0) ? node->qal[target] : -1;
			int logicalControl = (control >= 0) ? node->qal[control] : -1;
			
			bool good = true;
			bool dependsOnSomething = false;
			
			bool usesLogicalQubit = false;
			if(good && logicalTarget >= 0) {
				usesLogicalQubit = true;
			}
			if(good && logicalControl >= 0) {
				usesLogicalQubit = true;
			}
			good = good && usesLogicalQubit;
			
			//make sure this swap involves a qubit that has more CNOTs
			if(good && (noMoreCX[logicalTarget] && noMoreCX[logicalControl])) {
				good = false;
			}
			
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
			}
			
			int busyT = node->busyCycles(target);
			if(good && busyT) {
				dependsOnSomething = true;
				if(busyT > 1) {
					good = false;
				}
			}
			int busyC = node->busyCycles(control);
			if(good && busyC) {
				dependsOnSomething = true;
				if(busyC > 1) {
					good = false;
				}
			}
			if(good && node->cycle > 0 && nodesSize > 0 && !dependsOnSomething) {
				good = false;
			}
			if(good && isCyclic(node, g)) {
				good = false;
			}
			if(good) {
				numDependentGates++;
				possibleGates.push_back(g);
			}
		}
		if(nodesSize > 0 && !numDependentGates) {//this node can't lead to anything optimal
			//Reminder: this caused problems when I tried placing it before looking at swaps
			return true;
		}
		
		assert(possibleGates.size() < 64); //or else I need to do this differently
		unsigned long long numIters = 1LL << possibleGates.size();
		for(unsigned long long x = 0; x < numIters; x++) {
			//ToDo: investigate case where this if-statement evaluates to true:
			//if(node->parent && node->parent->dead) {
				//node->dead = true;
				//cerr << "ugh\n";
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
			
			if(!good) {
				delete child;
			} else {
				//schedule as many of the 1-cycle ready gates as we can:
				for(unsigned int y = 0; good && y < singleCycleGates.size(); y++) {
					child->scheduleGate(singleCycleGates[y]);
				}
				
				int cycleMod = (child->cycle < 0) ? child->cycle : 0;
				child->cycle -= cycleMod;
				child->cost = node->env->cost->getCost(child);
				child->cycle += cycleMod;
				
				if(!nodes->push(child)) {
					delete child;
				}
			}
		}
		
		return true;
	}
};

#endif
