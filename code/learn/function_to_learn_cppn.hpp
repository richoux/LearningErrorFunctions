#pragma once

#include <vector>
#include <functional>
// #include <ghost/variable.hpp>

using namespace std;
// using namespace ghost;

constexpr int number_units_transfo = 13;
constexpr int number_units_compar_1_param = 4;
constexpr int number_units_compar_2_params = 3;

// double g( const vector< reference_wrapper<Variable> >& weights,
//           const vector<int>& vars,
//           int max );

// double g( const vector< Variable >& weights,
//           const vector<int>& vars,
//           int max );

// double g( const vector< reference_wrapper<Variable> >& weights,
//           const vector<int>& vars,
//           int start,
//           int end,
//           int max );

double g( const vector< int >& weights,
          const vector<double>& vars,
          int start,
          int end,
          int nb_params,
          double parameter_1,
          double parameter_2 = 0 );
