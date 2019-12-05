#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

constexpr int number_units_transfo = 8;
constexpr int number_units_compar = 4;
constexpr int number_units_agreg = 2;
constexpr int number_units_arith = 2;

double g( const vector< Variable >& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int start,
          int nb_vars );

double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<double>& vars,
          int start,
          int end );

double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int start,
          int nb_vars );
