#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

vector< vector<int> > LHS( const vector< Variable >& variables, std::mt19937& gen );
vector< vector<int> > LHS( const vector< reference_wrapper<Variable> >& variables, std::mt19937& gen );
vector< vector<int> > LHS( int nb_vars, int var_max_value, std::mt19937& gen );
