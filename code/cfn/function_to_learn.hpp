#pragma once

#include <vector>
#include <ghost/variable.hpp>

using namespace std;

double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int max_value );
