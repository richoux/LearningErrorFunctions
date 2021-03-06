#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int var_max_value );
double g( const vector< Variable >& coeff, const vector<int>& vars, int var_max_value );

double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int start, int end, int var_max_value );
