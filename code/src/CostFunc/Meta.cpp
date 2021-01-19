#ifndef META_COSTFUNC_CPP
#define META_COSTFUNC_CPP

#include "Meta.hpp"
#include "CostFunc.hpp"
#include "CXFull.hpp"
#include "CXFrontier.hpp"
#include "SimpleCost.hpp"
#include <string>
#include <tuple>
using namespace std;

const int NUMCOSTFUNCTIONS = 5;
tuple<CostFunc*, string, string> costFunctions[NUMCOSTFUNCTIONS] = {
	make_tuple(new CXFrontier(),
				"CXFrontier",
				"Calculates lower-bound cost, including swaps to enable gates in the CX frontier"),
	make_tuple(new CXFull(),
				"CXFull",
				"Calculates lower-bound cost, including swaps to enable CX gates in remaining circuit"),
	make_tuple(new SimpleCost(),
				"SimpleCost",
				"Calculates lower-bound cost, assuming no more swaps will be inserted"),
};

#endif