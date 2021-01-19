#include "Node.hpp"
#include <set>
#include <cassert>
#include <iostream>
using namespace std;

//const int MAX_QUBITS = 20;
int GLOBALCOUNTER=0;

Node::Node() {
	for(int x = 0; x < MAX_QUBITS; x++) {
		qal[x] = x;
		laq[x] = x;
		lastNonSwapGate[x] = NULL;
		lastGate[x] = NULL;
	}
	this->cost = 0;
	this->dead = false;
}
	
Node::~Node() {
	scheduled->clean();
}

//schedule a gate, or return false if it conflicts with an active gate
//the gate parameter uses logical qubits (except in swaps); this function determines physical locations based on prior swaps
//the timeOffset can be used if we want to schedule a gate to start X cycles in the future
//this function adjusts qubit map when scheduling a swap
bool Node::scheduleGate(GateNode * gate, unsigned int timeOffset) {
	bool isSwap = !gate->name.compare("swp");
	isSwap = isSwap || !gate->name.compare("swp");
	
	int physicalControl = gate->control;
	int physicalTarget = gate->target;
	if(!isSwap) {
		if(physicalControl >= 0) {
			physicalControl = laq[physicalControl];
		}
		if(physicalTarget >= 0) {
			physicalTarget = laq[physicalTarget];
		}
	}
	
	int busyControl = this->busyCycles(physicalControl);
	if(physicalControl >= 0 && busyControl > 0 && busyControl > (int) timeOffset) {
		return false;
	}
	int busyTarget = this->busyCycles(physicalTarget);
	if(physicalTarget >= 0 && busyTarget > 0 && busyTarget > (int) timeOffset) {
		return false;
	}
	
	if(!isSwap) {
		//if appropriate, add double-child to ready gates
		if(gate->controlChild && gate->controlChild == gate->targetChild) {
			readyGates.insert(gate->controlChild);
		}
		//if appropriate, add control child to ready gates
		if(gate->controlChild && gate->controlChild != gate->targetChild) {
			if(gate->controlChild->control < 0) {//single-qubit gate
				readyGates.insert(gate->controlChild);
			} else {
				int childParentBit;
				GateNode * otherParent;
				if(gate->controlChild->controlParent == gate) {
					otherParent = gate->controlChild->targetParent;
					if(gate->controlChild->targetParent) {
						childParentBit = gate->controlChild->target;
					} else {
						childParentBit = -1;
					}
				} else {
					assert(gate->controlChild->targetParent == gate);
					otherParent = gate->controlChild->controlParent;
					if(gate->controlChild->controlParent) {
						childParentBit = gate->controlChild->control;
					} else {
						childParentBit = -1;
					}
				}
				if(childParentBit < 0 || (this->lastNonSwapGate[childParentBit] && this->lastNonSwapGate[childParentBit]->gate == otherParent)) {
					readyGates.insert(gate->controlChild);
				}
			}
		}
		//if appropriate, add target child to ready gates
		if(gate->targetChild && gate->controlChild != gate->targetChild) {
			if(gate->targetChild->control < 0) {//single-qubit gate
				readyGates.insert(gate->targetChild);
			} else {
				int childParentBit;
				GateNode * otherParent;
				if(gate->targetChild->controlParent == gate) {
					otherParent = gate->targetChild->targetParent;
					if(gate->targetChild->targetParent) {
						childParentBit = gate->targetChild->target;
					} else {
						childParentBit = -1;
					}
				} else {
					assert(gate->targetChild->targetParent == gate);
					otherParent = gate->targetChild->controlParent;
					if(gate->targetChild->controlParent) {
						childParentBit = gate->targetChild->control;
					} else {
						childParentBit = -1;
					}
				}
				if(childParentBit < 0 || (this->lastNonSwapGate[childParentBit] && this->lastNonSwapGate[childParentBit]->gate == otherParent)) {
					readyGates.insert(gate->targetChild);
				}
			}
		}
	}
	
	ScheduledGate * sg = new ScheduledGate(gate, this->cycle + timeOffset);
	sg->physicalControl = physicalControl;
	sg->physicalTarget = physicalTarget;
	
	if(physicalControl >= 0) {
		this->lastGate[physicalControl] = sg;
	}
	if(sg->gate->control >= 0 && !isSwap) {
		this->lastNonSwapGate[sg->gate->control] = sg;
	}
		
	if(physicalTarget >= 0) {
		this->lastGate[physicalTarget] = sg;
	}
	if(sg->gate->target >= 0 && !isSwap) {
		this->lastNonSwapGate[sg->gate->target] = sg;
	}
	
	if(!isSwap) {
		if(this->readyGates.erase(gate) != 1) {
			std::cerr << "FATAL ERROR: unable to remove scheduled gate from ready list.\n";
			std::cerr << "\tGate name: " << gate->name << "\n";
			std::cerr << "\tTime offset: " << timeOffset << "\n";
			assert(false);
		}
		this->numUnscheduledGates--;
	}
	
	this->scheduled = this->scheduled->push(sg);
	
	//adjust qubit map
	if(isSwap) {
		if(qal[physicalControl] >= 0 && qal[physicalTarget] >= 0) {
			std::swap(laq[(int)qal[physicalControl]], laq[(int)qal[physicalTarget]]);
		} else if(qal[physicalControl] >= 0) {
			laq[(int)qal[physicalControl]] = physicalTarget;
		} else if(qal[physicalTarget] >= 0) {
			laq[(int)qal[physicalTarget]] = physicalControl;
		} else {
			assert(false);
		}
		std::swap(qal[physicalControl], qal[physicalTarget]);
	}
	
	return true;
}
	
//prepares a new child node (without scheduling any more gates)
Node * Node::prepChild() {
	Node * child = new Node;
	child->numUnscheduledGates = this->numUnscheduledGates;
	child->env = this->env;
	child->parent = this;
	child->cycle = this->cycle + 1;
	child->readyGates = this->readyGates;//note: this actually produces a separate copy
	child->scheduled = scheduled->newRef();
	for(int x = 0; x < env->numPhysicalQubits; x++) {
		child->qal[x] = this->qal[x];
		child->laq[x] = this->laq[x];
		child->lastNonSwapGate[x] = this->lastNonSwapGate[x];
		child->lastGate[x] = this->lastGate[x];
	}
	child->cost = 0;//Remember to calculate cost in expander, *after* it's done scheduling new gates for this node //child->cost = env->cost->getCost(child);
	
	return child;
}
