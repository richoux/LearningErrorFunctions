#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr : public Constraint
{
	mutable std::mt19937 gen;
	mutable uniform_int_distribution<> rand_var;
	mutable uniform_int_distribution<> rand_val;

	double required_cost() const override;

public:
	Ctr( const vector< reference_wrapper<Variable> >& variables, const std::mt19937& gen );
};
