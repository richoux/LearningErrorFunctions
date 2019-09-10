#pragma once

#include <vector>
#include <ghost/variable.hpp>

using namespace ghost;
using namespace std;

vector< vector<int> > random_draw( const vector< Variable >& variables );
vector< vector<int> > random_draw( int nb_vars, int max_value );
