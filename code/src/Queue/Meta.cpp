#ifndef META_QUEUES_CPP
#define META_QUEUES_CPP

#include "Meta.hpp"
#include "Queue.hpp"
#include "DefaultQueue.hpp"
#include "TrimSlowNodes.hpp"
#include <string>
#include <tuple>
using namespace std;

const int NUMQUEUES = 2;
tuple<Queue*, string, string> queues[NUMQUEUES] = {
	make_tuple(new DefaultQueue(),
				"DefaultQueue",
				"uses std priority_queue."),
	make_tuple(new TrimSlowNodes(),
				"TrimSlowNodes",
				"Takes 2 params; when reaching max # nodes it removes slowest until it reaches target # nodes."),
};

#endif