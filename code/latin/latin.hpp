#pragma once

#include <vector>
#include <functional>
#include <ghost/variable.hpp>

#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

class LHS
{
	mutable randutils::mt19937_rng _rng;
	
public:
	LHS() = default;
	
	vector<int> sample( int nb_vars, int var_max_value ) const;
};
