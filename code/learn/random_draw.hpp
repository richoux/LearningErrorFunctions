#pragma once

#include <vector>
#include <ghost/variable.hpp>

#include "../constraints/concept.hpp"

using namespace ghost;
using namespace std;

void random_draw( unique_ptr<Concept>& concept,
                  int nb_vars,
                  int max_value,
                  vector<int>& solutions,
                  vector<int>& not_solutions,
                  double percent = 0.1 );
