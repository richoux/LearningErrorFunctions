#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

constexpr int number_units_transfo = 18;
constexpr int number_units_compar = 8;
constexpr int number_units_aggreg = 1;
constexpr int number_units_arith = 1;

double g( const vector< Variable >& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int max_domain_value,
          int start,
          int nb_vars );

double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<double>& vars,
          int max_domain_value,
          int start,
          int end );

double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int max_domain_value,
          int start,
          int nb_vars );
