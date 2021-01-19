#ifndef CXFULL_HPP
#define CXFULL_HPP

#include "CostFunc.hpp"
#include "Node.hpp"
#include <cassert>

class CXFull : public CostFunc {
  public:
	int _getCost(Node * node) {
		bool debug = node->cost > 0;//called getCost for second time on this node
		
		int cost = 0;
		int costT = 99999;
		Environment * env = node->env;
		GateNode * next2BitGate[env->numPhysicalQubits];
		int pathLength[env->numPhysicalQubits];
		GateNode * next2BitGate2[env->numPhysicalQubits];
		for(int x = 0; x < env->numPhysicalQubits; x++) {
			next2BitGate[x] = NULL;
			next2BitGate2[x] = NULL;
			pathLength[x] = 0;
			int busy = node->busyCycles(x);
			if(busy > cost) {
				cost = busy;
			}
		}
		
		//search from last scheduled (non-swap) gates
		for(int x = 0; x < env->numPhysicalQubits; x++) {
			ScheduledGate * sg = node->lastNonSwapGate[x];
			if(sg) {
				//get latest physical location of logical qubit x:
				int actualQubit;
				if(sg->gate->target == x) {
					actualQubit = node->laq[sg->gate->target];
				} else {
					assert(sg->gate->control == x);
					actualQubit = node->laq[sg->gate->control];
				}
				
				//get path length to next 2-qubit gate along this qubit:
				pathLength[actualQubit] = node->busyCycles(actualQubit);
				if(!pathLength[actualQubit]) {
					pathLength[actualQubit] = 1;//since we won't schedule any more gates this cycle
				}
				GateNode * temp;
				if(sg->gate->target == x) {
					temp = sg->gate->targetChild;
				} else {
					assert(sg->gate->control == x);
					temp = sg->gate->controlChild;
				}
				
				while(temp && temp->control < 0) {
					pathLength[actualQubit] += temp->latency;
					temp = temp->targetChild;
				}
				next2BitGate[actualQubit] = temp;
			}
		}
		
		//also search from ready gates, in case some qubits haven't scheduled gates yet
		auto iter = node->readyGates.begin();
		while(iter != node->readyGates.end()) {
			GateNode * g = *iter;
			int physicalTarget = node->laq[g->target];
			
			if(physicalTarget < 0) {
				iter++;
				continue;
			}
			
			if(g->control < 0) {
				//if(next2BitGate[physicalTarget] == NULL) {
					pathLength[physicalTarget] = node->busyCycles(physicalTarget);
					if(!pathLength[physicalTarget]) {
						pathLength[physicalTarget] = 1;//since we won't schedule any more gates this cycle
					}
					GateNode * temp = g;
					while(temp && temp->control < 0) {
						pathLength[physicalTarget] += temp->latency;
						temp = temp->targetChild;
					}
					next2BitGate[physicalTarget] = temp;
					
					if(temp) {
						int otherBit;
						bool noOtherParent = false;
						if(temp->target == g->target) {
							noOtherParent = temp->controlParent == NULL;
							otherBit = node->laq[temp->control];
						} else {
							assert(temp->control == g->target);
							noOtherParent = temp->targetParent == NULL;
							otherBit = node->laq[temp->target];
						}
						if(noOtherParent && next2BitGate[otherBit] == NULL) {
							next2BitGate[otherBit] = temp;
							pathLength[otherBit] = node->busyCycles(otherBit);
							if(!pathLength[otherBit]) {
								pathLength[otherBit] = 1;//since we won't schedule any more gates this cycle
							}
						}
					}
				//}
			} else {
				int physicalControl = node->laq[g->control];
				if(physicalControl < 0) {
					iter++;
					continue;
				}
				assert(next2BitGate[physicalControl] == g || next2BitGate[physicalControl] == NULL);
				assert(next2BitGate[physicalTarget] == g || next2BitGate[physicalTarget] == NULL);
				
				pathLength[physicalTarget] = node->busyCycles(physicalTarget);
				if(!pathLength[physicalTarget]) {
					pathLength[physicalTarget] = 1;//since we won't schedule any more gates this cycle
				}
				next2BitGate[physicalTarget] = g;
				
				pathLength[physicalControl] = node->busyCycles(physicalControl);
				if(!pathLength[physicalControl]) {
					pathLength[physicalControl] = 1;//since we won't schedule any more gates this cycle
				}
				next2BitGate[physicalControl] = g;
			}
			
			/*
			int cost1 = g->criticality + g->latency + node->busyCycles(physicalTarget);
			if(cost1 > cost) {
				if(debug) std::cerr << "  up subcircuit cost to " << cost1 << " based on ready " << physicalTarget << " gate" << "\n";
				cost = cost1;
			}
			*/
			
			iter++;
		}
		
		//analyze iterative cnot frontiers
		bool nonemptyFrontier = true;
		int iterNum = -1;
		while(nonemptyFrontier) {
			iterNum++;
			nonemptyFrontier = false;
			for(int x = 0; x < env->numPhysicalQubits; x++) {
				GateNode * g = next2BitGate[x];
				next2BitGate2[x] = NULL;
				if(g) {
					if(debug) std::cerr << "  considering next gate for physical qubit " << x << "\n";
					if(debug) std::cerr << "   logical qubits: " << g->control << "," << g->target << "\n";
					int physicalTarget = node->laq[g->target];
					int physicalControl = node->laq[g->control];
					
					if(debug) std::cerr << "   physical qubits: " << physicalControl << "," << physicalTarget << "\n";
					
					assert(physicalTarget == x || physicalControl == x);
					assert(physicalTarget != physicalControl);
					//assert(physicalTarget >= 0 && physicalControl >= 0);
					if(physicalTarget < 0 || physicalControl < 0) {
						continue;
					}
					
					int length1 = pathLength[physicalTarget];
					int length2 = pathLength[physicalControl];
					
					//skip if this cnot depends on another unscheduled cnot
					if(next2BitGate[physicalTarget] != next2BitGate[physicalControl]) {
						if(debug) std::cerr << "   skipping (non-frontier)\n";
						continue;
					}
					
					nonemptyFrontier = true;
					next2BitGate2[x] = g;
					
					//skip if we already processed this in earlier iteration:
					if(physicalTarget <= x && physicalControl <= x) {
						if(debug) std::cerr << "   skipping (already checked)\n";
						continue;
					}
					
					int minSwaps = env->couplingDistances[physicalControl*env->numPhysicalQubits + physicalTarget] - 1;
					if(!iterNum && minSwaps < costT) costT = minSwaps;
					int totalSwapCost = env->swapCost * minSwaps;
					
					if(length1 < length2) {
						std::swap(length1, length2);
					}
					
					if(debug) std::cerr << "   path lengths: " << length1 << "," << length2 << "\n";
					if(debug) std::cerr << "   swaps needed at least: " << minSwaps << "\n";
					
					int slack = length1-length2;
					int effectiveSlack = (slack/env->swapCost) * env->swapCost;
					if(effectiveSlack > totalSwapCost) {
						effectiveSlack = totalSwapCost;
					}
					
					if(debug) std::cerr << "   effective slack cycles: " << effectiveSlack << "\n";
					
					int mutualSwapCost = totalSwapCost - effectiveSlack;
					int extraSwapCost = (0x1 & (mutualSwapCost/env->swapCost)) * env->swapCost;
					mutualSwapCost -= extraSwapCost;
					assert((mutualSwapCost % env->swapCost) == 0);
					mutualSwapCost = mutualSwapCost >> 1;
					
					int cost1 = g->latency + g->criticality + length1 + mutualSwapCost;
					int cost2 = g->latency + g->criticality + length2 + mutualSwapCost + effectiveSlack;
					
					if(cost1 < cost2) {
						cost1 += extraSwapCost;
					} else {
						cost2 += extraSwapCost;
					}
					
					if(debug) std::cerr << "   shared swap cycles: " << mutualSwapCost << "\n";
					if(debug) std::cerr << "   criticality: " << g->criticality << "\n";
					
					if(debug) std::cerr << "   subcircuit cost: " << cost1 << " vs " << cost2 << "\n";
					
					if(cost1 > cost) {
						cost = cost1;
					}
					if(cost2 > cost) {
						cost = cost2;
					}
				}
			}
			
			if(!nonemptyFrontier) {
				break;
			}
			
			for(int x = 0; x < env->numPhysicalQubits; x++) {
				if(next2BitGate[x] && next2BitGate2[x] == next2BitGate[x]) {
					GateNode * g = next2BitGate[x];
					int addlPath = g->latency;
					int physicalTarget = node->laq[g->target];
					int physicalControl = node->laq[g->control];
					if(physicalTarget == x) {
						g = g->targetChild;
					} else {
						assert(physicalControl == x);
						g = g->controlChild;
					}
					
					while(g && g->control < 0) {
						addlPath += g->latency;
						g = g->targetChild;
					}
					
					if(g) {
						next2BitGate[x] = g;
						pathLength[x] += addlPath;
					} else {
						next2BitGate[x] = NULL;
					}
				}
			}
		}
		
		//add old cycles to cost
		cost += node->cycle;
		
		/*
		//Since this function is either buggy or CANNOT overestimate cost, use parent cost if larger
		if(node->parent && node->parent->cost > cost) {
			cost = node->parent->cost;
		}
		*/
		
		if(costT == 99999) costT = 0;
		node->cost2 = costT;
		
		return cost;
	}
};

#endif
