#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../latin/latin.hpp"
#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

class Ctr_smooth : public Constraint
{
	int _nb_vars;
	int _var_max_value;

	LHS _latin;
	mutable randutils::mt19937_rng _rng;
	
	double required_cost() const override;

public:
	Ctr_smooth( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value );
};
