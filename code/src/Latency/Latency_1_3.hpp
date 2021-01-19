#include "Latency.hpp"

//Latency example: 3 cycles per SWP; 1 cycle otherwise
class Latency_1_3 : public Latency {
  public:
	int getLatency(string gateName, int control) {
		if(!gateName.compare("swp") || !gateName.compare("SWP")) {
			return 3;
		} else {
			return 1;
		}
	}
};
