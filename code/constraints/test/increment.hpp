#pragma once

#include <memory>
#include <vector>

#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

bool increment( const vector<reference_wrapper<Variable>> & );

void increment_some_vars( const vector<reference_wrapper<Variable>> &,
                          const vector<int>& );

void increment_boolean_vector( vector<bool> & );
