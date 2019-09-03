#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

vector< vector<int> > LHS( const vector< Variable >& variables, std::mt19937& gen );
