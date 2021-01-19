#ifndef META_EXPANDERS_CPP
#define META_EXPANDERS_CPP

#include "Meta.hpp"
#include "Expander.hpp"
#include "DefaultExpander.hpp"
#include "GreedyTopK.hpp"
#include "NoSwaps.hpp"
#include <string>
#include <tuple>
using namespace std;

const int NUMEXPANDERS = 3;
tuple<Expander*, string, string> expanders[NUMEXPANDERS] = {
	make_tuple(new DefaultExpander(),
				"DefaultExpander",
				"The default expander. Includes acyclic swap and dependent state optimizations."),
	make_tuple(new GreedyTopK(),
				"GreedyTopK",
				"Keep only top K nodes; avoids some swaps and schedules original gates ASAP [non-optimal!]"),
	make_tuple(new NoSwaps(),
				"NoSwaps",
				"Cannot insert swaps."),
};

#endif