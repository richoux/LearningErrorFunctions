#pragma once

#include <vector>
#include <ghost/variable.hpp>

using namespace ghost;
using namespace std;

void random_draw( const vector< Variable >& variables, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent = 1. );
void random_draw( int nb_vars, int max_value, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent = 1. );
