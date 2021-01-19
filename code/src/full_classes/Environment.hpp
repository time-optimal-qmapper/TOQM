#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

class GateNode;
class CostFunc;
class Latency;
#include "Filter.hpp"
#include "NodeMod.hpp"
#include <set>
#include <vector>
using namespace std;

class Environment {//for data shared across all nodes
  public:
	vector<NodeMod*> nodeMods;
	vector<Filter*> filters;
	CostFunc * cost;//contains function to calculate a node's cost
	Latency * latency;//contains function to calculate a gate's latency
	set<pair<int, int> > couplings; //the coupling map (as a list of qubit-pairs)
	GateNode ** possibleSwaps;
	
	int numLogicalQubits;
	int numPhysicalQubits;
	int * couplingDistances;//array of size (numPhysicalQubits*numPhysicalQubits)
	int swapCost; //should be set by main using the latency function
	int numGates;
	
	GateNode ** firstCXPerQubit = 0;
	
	void runNodeModifiers(Node * node, int flag) {
		for(unsigned int x = 0; x < this->nodeMods.size(); x++) {
			this->nodeMods[x]->mod(node, flag);
		}
	}
	
	bool filter(Node * newNode) {
		for(unsigned int x = 0; x < this->filters.size(); x++) {
			if(this->filters[x]->filter(newNode)) {
				for(unsigned int y = 0; y < x; y++) {
					this->filters[y]->deleteRecord(newNode);
				}
				return true;
			}
		}
		
		return false;
	}
	
	void deleteRecord(Node * oldNode) {
		for(unsigned int x = 0; x < this->filters.size(); x++) {
			this->filters[x]->deleteRecord(oldNode);
		}
	}
	
	void resetFilters() {
		for(unsigned int x = 0; x < this->filters.size(); x++) {
			Filter * old = this->filters[x];
			this->filters[x] = old->createEmptyCopy();
			delete old;
		}
	}
	
	void printFilterStats(std::ostream & stream) {
		for(unsigned int x = 0; x < this->filters.size(); x++) {
			this->filters[x]->printStatistics(stream);
		}
	}
};

#endif
