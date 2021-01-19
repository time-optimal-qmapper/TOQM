#ifndef GATENODE_HPP
#define GATENODE_HPP

#include <string>
using namespace std;

class GateNode { //part of a DAG of nodes
  public:
	string name;
	int control;//control qubit, or -1
	int target;//target qubit
	
	int latency;//how many cycles this gate takes
	int criticality;//length (time) of circuit from here until furthest leaf
	
	//note that the following variables will not take into account inserted SWP gates
	GateNode * controlChild = 0;//gate which depends on this one's control qubit, or NULL
	GateNode * targetChild = 0;//gate which depends on this one's target qubit, or NULL
	GateNode * controlParent = 0;//prior gate which this control qubit depends on, or NULL
	GateNode * targetParent = 0;//prior gate which this target qubit depends on, or NULL
	
	GateNode * nextControlCNOT = 0;//next 2-qubit gate which depends on this one's control, or -1
	GateNode * nextTargetCNOT = 0;//next 2-qubit gate which depends on this one's target, or -1
};

#endif
