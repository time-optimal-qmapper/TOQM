#ifndef EXPAND_HPP
#define EXPAND_HPP

class Node;
class Queue;

class Expander {
  public:
	virtual ~Expander() {};
	
	//expands given node, unless it has same-or-worse cost than best final node
	//returns false iff given node's cost >= best final node's cost
	virtual bool expand(Queue * nodes, Node * node) =0;
	
	virtual int setArgs(char** argv) {
		//used to set the expander's parameters via command-line
		//return number of args consumed
		
		return 0;
	}
	
	virtual int setArgs() {
		//used to set the expander's parameters via-cin
		//return number of args consumed
		
		return 0;
	}
};

#endif
