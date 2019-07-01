#pragma once

#include <memory>
#include <vector>

#include "subghost/variable.hpp"

using namespace std;
using namespace ghost;

void increment( const vector<reference_wrapper<Variable>> &, const int );
void increment( const vector<reference_wrapper<Variable>> &, const int, const int );
