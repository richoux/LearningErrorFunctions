#pragma once

#include <vector>
#include <functional>
#include <random>
#include <algorithm>

#include "../utils/randutils.hpp"

using namespace std;

class LHS
{
	mutable randutils::mt19937_rng _rng;
	mutable std::random_device _rd;
	mutable std::mt19937 _rng_std;
	
public:
	LHS() = default;
	
	vector<int> sample( int nb_vars, int var_max_value ) const;
};
