#include "Queue.hpp"
#include <queue>
#include <vector>
#include <iostream>

extern bool _verbose;

class TrimSlowNodes : public Queue {
  private:
	unsigned int maxSize = 1000;
	unsigned int targetSize = 500;
	
	struct CmpCost {
		bool operator()(const Node* lhs, const Node* rhs) const
		{
			//tiebreaker:
			if(lhs->cost == rhs->cost) {
				//return lhs->scheduled->size > rhs->scheduled->size;
				//return lhs->numUnscheduledGates > rhs->numUnscheduledGates;
				//return lhs->cycle < rhs->cycle;
				return lhs->debugID < rhs->debugID;
			}
			
			//lower cost is better
			return lhs->cost > rhs->cost;
		}
	};
	
	struct CmpProgress {
		bool operator()(const Node* lhs, const Node* rhs) const
		{
			//tiebreaker:
			if(lhs->numUnscheduledGates == rhs->numUnscheduledGates) {
				if(lhs->cost ==- rhs->cost) {
					return lhs->debugID < rhs->debugID;
				} else {
					return lhs->cost > rhs->cost;
				}
			}
			
			//fewer not-yet-scheduled gates is better
			return lhs->numUnscheduledGates > rhs->numUnscheduledGates;
		}
	};
	
	/**
	 * The queue containing the nodes
	 */
    std::priority_queue<Node*, std::vector<Node*>, CmpCost> nodes;
	
	/**
	 * A temporary queue used to organize nodes by progress through the original circuit
	 */
	std::priority_queue<Node*, std::vector<Node*>, CmpProgress> tempQueue;
	
	bool pushNode(Node * newNode) {
		nodes.push(newNode);
		if(_verbose) {
			if(newNode->numUnscheduledGates < garbage) {
				garbage = newNode->numUnscheduledGates;
				garbage2 = newNode->cost;
				
				std::cerr << "dbg More progress!\n";
				std::cerr << " " << garbage << " gates remain!\n";
				std::cerr << " cost is " << newNode->cost << "\n";
				if(newNode->parent)
					std::cerr << " parent cost is " << newNode->parent->cost << "\n";
				else
					std::cerr << " root node!\n";
				std::cerr << " num ready gates is " << newNode->readyGates.size() << "\n";
			} else if(newNode->numUnscheduledGates == garbage) {
				if(newNode->cost < garbage2) {
					garbage2 = newNode->cost;
					std::cerr << "dbg Better progress!\n";
					std::cerr << " new cost is " << newNode->cost << "\n";
				}
			}
		}
		
		if(nodes.size() > maxSize) {
			if(_verbose) {
				std::cerr << "dbg Queue needs trimming...\n";
			}
			
			//Move all nodes to queue that sorts them by progress
			while(nodes.size() > 0) {
				tempQueue.push(nodes.top());
				nodes.pop();
			}
			//Move top nodes back to main queue
			for(unsigned int x = 0; x < this->targetSize; x++) {
				nodes.push(tempQueue.top());
				tempQueue.pop();
			}
			//Delete the rest of the nodes
			while(tempQueue.size() > 0) {
				Node * n = tempQueue.top();
				tempQueue.pop();
				n->env->deleteRecord(n);
				delete n;
			}
		}
		
		return true;
	}
	
	int garbage = 9999999;
	int garbage2 = 9999999;
	
  public:
	int setArgs(char** argv) {
		this->maxSize = atoi(argv[0]);
		this->targetSize = atoi(argv[1]);
		if(this->maxSize < this->targetSize) {
			std::swap(this->maxSize, this->targetSize);
		}
		assert(this->maxSize != this->targetSize);
		return 2;
	}
	
	int setArgs() {
		std::cerr << "Enter max size and then target size for queue:\n";
		std::cin >> this->maxSize;
		std::cin >> this->targetSize;
		if(this->maxSize < this->targetSize) {
			std::swap(this->maxSize, this->targetSize);
		}
		assert(this->maxSize != this->targetSize);
		return 2;
	}
	
	Node * pop() {
		numPopped++;
		
		Node * ret = nodes.top();
		nodes.pop();
		
		//std::cerr << "Debug message: popped node with cost " << ret->cost << "\n";
		//std::cerr << "Debug message: queue has size " << nodes.size() << " now.\n";
		
		if(!ret->readyGates.size()) {
			assert(ret->numUnscheduledGates == 0);
			bool done = true;
			if(done) {
				if(!bestFinalNode) {
					if(_verbose) std::cerr << "dbg msg: found a final node.\n";
					bestFinalNode = ret;
				} else if(ret->cost < bestFinalNode->cost) {
					if(_verbose)  std::cerr << "dbg msg: found a better final node.\n";
					//delete bestFinalNode;
					bestFinalNode = ret;
				}
			}
		}
		
		return ret;
	}
	
	int size() {
		return nodes.size();
	}
};
