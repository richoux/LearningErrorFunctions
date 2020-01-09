#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr_unique_agreg_function : public Constraint
{
	double required_cost() const override;

public:
	Ctr_unique_agreg_function( const vector< reference_wrapper<Variable> >& weights );
};
