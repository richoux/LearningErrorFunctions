#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;

vector< vector<int> > LHS( const vector< reference_wrapper<ghost::Variable> >& variables );
vector< vector<int> > LHS( int nb_vars, int var_max_value );
