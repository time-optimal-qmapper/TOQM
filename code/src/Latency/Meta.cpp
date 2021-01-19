#ifndef META_LATENCY_CPP
#define META_LATENCY_CPP

#include "Meta.hpp"
#include "Latency.hpp"
#include "Latency_1_2_6.hpp"
#include "Latency_1_3.hpp"
#include "Latency_1.hpp"
#include <string>
#include <tuple>
using namespace std;

const int NUMLATENCIES = 3;
tuple<Latency*, string, string> latencies[NUMLATENCIES] = {
	make_tuple(new Latency_1_2_6(),
				"Latency_1_2_6",
				"swap cost 6, 2-bit gate cost 2, 1-bit gate cost 1."),
	make_tuple(new Latency_1_3(),
				"Latency_1_3",
				"swap cost 3, all else cost 1."),
	make_tuple(new Latency_1(),
				"Latency_1",
				"every gate takes 1 cycle."),
};

#endif