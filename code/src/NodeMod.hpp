#ifndef NODEMOD_HPP
#define NODEMOD_HPP

class Node;

#define MOD_TYPE_BEFORECOST 1

class NodeMod {
  public:
	virtual ~NodeMod() {};
	
	virtual void mod(Node * node, int flag) = 0;
	
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
