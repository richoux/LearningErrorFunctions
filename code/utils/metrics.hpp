#pragma once

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <functional>

#include "convert.hpp"

using namespace std;

double hamming_metric( const vector<int>& configuration,
                       const vector<int>& solution,
                       int start_config,
                       int start_sol,
                       int nb_vars );

double hamming_manhattan_metric( const vector<int>& configuration,
                                 const vector<int>& solution,
                                 int start_config,
                                 int start_sol,
                                 int nb_vars,
                                 int max_value );

map<string, double> compute_metric( const vector<int>& random_solutions,
                                    const vector<int>& random_configurations,
                                    int nb_vars,
                                    int max_value );

map<string, double> compute_metric_hamming_only( const vector<int>& random_solutions,
                                                 const vector<int>& random_configurations,
                                                 int nb_vars );
