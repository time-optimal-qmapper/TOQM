#ifndef SIMPLECOST_HPP
#define SIMPLECOST_HPP

#include "CostFunc.hpp"
#include "Node.hpp"
#include <cassert>

//CostFunc example
class SimpleCost : public CostFunc {
  public:
	int _getCost(Node * node) {
		bool debug = node->cost > 0;
		
		int cost = 0;
		int costT = 99999;
		Environment * env = node->env;
		
		//Calculate remaining cost of scheduled gates that haven't finished
		int busyCyclesRemaining[env->numPhysicalQubits];
		for(int x = 0; x < env->numPhysicalQubits; x++) {
			busyCyclesRemaining[x] = node->busyCycles(x);
			if(debug) {
				//std::cerr << x << " busy for " << busyCyclesRemaining[x] << "\n";
			}
			if(busyCyclesRemaining[x] > cost) {
				cost = busyCyclesRemaining[x];
			}
		}
		
		//Consider cost of unscheduled gates
		auto iter = node->readyGates.begin();
		while(iter != node->readyGates.end()) {
			GateNode * g = *iter;
			
			int tempcost = g->criticality + g->latency;
			int tempcost2 = tempcost;
			
			int control = -1;
			if(g->control >= 0) {
				control = node->laq[g->control];
			}
			int target = -1;
			if(g->target >= 0) {
				target = node->laq[g->target];
			}
			
			if(control >= 0) {
				if(busyCyclesRemaining[control]) {
					tempcost += busyCyclesRemaining[control];
				} else {
					tempcost += 1;//take into account that we're not scheduling any more gates this cycle
				}
			}
			if(target >= 0) {
				if(busyCyclesRemaining[target]) {
					tempcost2 += busyCyclesRemaining[target];
				} else {
					tempcost2 += 1;//take into account that we're not scheduling any more gates this cycle
				}
			}
			
			if(control >= 0 && target >= 0) {
				int dist = env->couplingDistances[control*env->numPhysicalQubits + target];
				if(dist < costT) costT = dist - 1;
				int minSwapCost = env->swapCost * (dist / 2);
				assert(minSwapCost >= 0);
				
				if(debug) {
					std::cerr << target << " busy for " << busyCyclesRemaining[target] << "\n";
					std::cerr << control << " busy for " << busyCyclesRemaining[control] << "\n";
					std::cerr << "dist: " << dist << ", swapCostPerQ: " << minSwapCost << "\n";
				}
				
				if(dist > 1) {//at least one node between target and control
					if(dist & 0x1) {//odd dist; therefore even nodes between target and control
						tempcost += minSwapCost;
						tempcost2 += minSwapCost;
					} else if(tempcost < tempcost2) {
						tempcost += minSwapCost;
						tempcost2 += minSwapCost - env->swapCost;
					} else {
						tempcost2 += minSwapCost;
						tempcost += minSwapCost - env->swapCost;
					}
				}
			}
			
			if(tempcost > cost) {
				cost = tempcost;
			}
			if(tempcost2 > cost) {
				cost = tempcost2;
			}
			
			if(debug) {
				std::cerr << control << "," << target << ":" << g->criticality + g->latency << ":" << "\t" << tempcost << " or " << tempcost2 << "\n";
			}
			
			iter++;
		}
		
		//Consider cost of completed gates
		cost += node->cycle;
		
		if(debug) std::cerr << " COST: " << cost << " (" << node->cycle << " + " << (cost-node->cycle) << ")" << "\n";
		
		if(costT == 99999) costT = 0;
		node->cost2 = costT;
		
		return cost;
	}
};

#endif
