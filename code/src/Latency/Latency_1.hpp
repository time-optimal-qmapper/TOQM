#ifndef LATENCY_1_HPP
#define LATENCY_1_HPP

#include "Latency.hpp"

//Latency example: 1 cycle for EVERY gate
class Latency_1 : public Latency {
  public:
	int getLatency(string gateName, int control) {
		return 1;
	}
};

#endif
