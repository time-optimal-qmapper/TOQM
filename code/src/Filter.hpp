#ifndef FILTER_HPP
#define FILTER_HPP

class Node;
class Queue;
#include <iostream>

class Filter {
  public:
	virtual ~Filter() {};
	
	//this should be called after we're done scheduling gates in newNode
	//return true iff we don't want to add newNode to the nodes list
	virtual bool filter(Node * newNode) = 0;
	
	virtual void printStatistics(std::ostream & stream) {
		//this function should print info such as how many nodes have been filtered out
	}
	
	virtual void deleteRecord(Node * n) {
		//if this filter retains node info, delete the filter's records of node n
	}
	
	virtual Filter * createEmptyCopy() = 0;
	
	virtual int setArgs(char** argv) {
		//used to set the queue's parameters via command-line
		//return number of args consumed
		
		return 0;
	}
	
	virtual int setArgs() {
		//used to set the queue's parameters via std::cin
		//return number of args consumed
		
		return 0;
	}
};

#endif
