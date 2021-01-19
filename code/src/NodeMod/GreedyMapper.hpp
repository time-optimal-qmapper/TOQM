#include "NodeMod.hpp"
#include "Node.hpp"
#include <iostream>

class GreedyMapper : public NodeMod {
  private:

  public:
  
	void mod(Node * node, int flag) {
		//Return unless this was called before calculating node's cost
		if(flag != MOD_TYPE_BEFORECOST) {
			return;
		}
		
		Environment * env = node->env;
		
		//if this is the root node, unmap the qubits
		if(node->cycle < 0 && node->parent == NULL) {
			for(int x = 0; x < env->numPhysicalQubits; x++) {
				node->laq[x] = -1;
				node->qal[x] = -1;
			}
		}
		
		//return unless there are unmapped qubits
		bool mayNeedAssignment = false;
		for(int x = 0; x < env->numLogicalQubits; x++) {
			if(node->laq[x] < 0) {
				mayNeedAssignment = true;
				break;
			}
		}
		if(!mayNeedAssignment) {
			return;
		}
		
		for(auto iter = node->readyGates.begin(); iter != node->readyGates.end(); iter++) {
			GateNode * g = *iter;
			
			if(g && g->control < 0) {
				//g = g->nextTargetCNOT ? g->nextTargetCNOT : g;
			}
			
			if(g && g->control >= 0) {
				int physC = node->laq[g->control];
				int physT = node->laq[g->target];
				if(physC < 0 && physT < 0) {
					int bestTarget = -1;
					int bestControl = -1;
					int bestDistance = 2 * env->numPhysicalQubits * env->numPhysicalQubits;
					for(int x = 0; x < env->numPhysicalQubits - 1; x++) {
						if(node->qal[x] < 0) {
							for(int y = x + 1; y < env->numPhysicalQubits; y++) {
								if(node->qal[y] < 0) {
									int dist = env->couplingDistances[x * env->numPhysicalQubits + y];
									if(dist < bestDistance) {
										bestTarget = x;
										bestControl = y;
										bestDistance = dist;
									}
								}
							}
						}
					}
					
					//cerr << bestTarget << " ";
					//std::swap(bestTarget, bestControl);
					//cerr << bestTarget << "\n";
					
					assert(bestTarget >= 0);
					node->laq[g->control] = bestControl;
					node->laq[g->target] = bestTarget;
					node->qal[bestControl] = g->control;
					node->qal[bestTarget] = g->target;
						
				} else if(physC < 0) {
					int bestBit = -1;
					int bestDistance = 2 * env->numPhysicalQubits * env->numPhysicalQubits;
					for(int x = 0; x < env->numPhysicalQubits; x++) {
						if(x != physT) {
							if(node->qal[x] < 0) {
								int dist = env->couplingDistances[x * env->numPhysicalQubits + physT];
								if(dist < bestDistance) {
									bestBit = x;
									bestDistance = dist;
								}
							}
						}
					}
					
					assert(bestBit >= 0);
					node->laq[g->control] = bestBit;
					node->qal[bestBit] = g->control;
				} else if(physT < 0) {
					int bestBit = -1;
					int bestDistance = 2 * env->numPhysicalQubits * env->numPhysicalQubits;
					for(int x = 0; x < env->numPhysicalQubits; x++) {
						if(x != physC) {
							if(node->qal[x] < 0) {
								int dist = env->couplingDistances[x * env->numPhysicalQubits + physC];
								if(dist < bestDistance) {
									bestBit = x;
									bestDistance = dist;
								}
							}
						}
					}
					
					assert(bestBit >= 0);
					node->laq[g->target] = bestBit;
					node->qal[bestBit] = g->target;
				}
			} else if(false && g) {
				for(int x = 0; x < env->numPhysicalQubits; x++) {
					if(node->qal[x] < 0) {
						node->laq[g->target] = x;
						node->qal[x] = g->target;
						break;
					}
				}
			}
		}
	}
};
