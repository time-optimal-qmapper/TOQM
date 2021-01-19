#ifndef META_FILTERS_CPP
#define META_FILTERS_CPP

#include "Meta.hpp"
#include "Filter.hpp"
#include "HashFilter.hpp"
#include "HashFilter2.hpp"
#include <string>
#include <tuple>
using namespace std;

const int NUMFILTERS = 2;
tuple<Filter*, string, string> FILTERS[NUMFILTERS] = {
	make_tuple(new HashFilter(),
				"HashFilter",
				"using hash, this tries to filter out worse nodes."),
	make_tuple(new HashFilter2(),
				"HashFilter2",
				"using hash, this tries to filter out worse nodes, or mark old nodes as dead if a new node is strictly-better."),
};

#endif