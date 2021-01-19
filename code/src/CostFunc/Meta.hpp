#ifndef META_COSTFUNC_HPP
#define META_COSTFUNC_HPP

#include "CostFunc.hpp"
#include <string>
#include <tuple>
using namespace std;

extern const int NUMCOSTFUNCTIONS;
extern tuple<CostFunc*, string, string> costFunctions[];

#endif