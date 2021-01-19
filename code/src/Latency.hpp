#ifndef LATENCY_HPP
#define LATENCY_HPP

#include <string>
using namespace std;

class Latency {
  public:
	virtual ~Latency() {};
	virtual int getLatency(string gateName, int control) =0;
	
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