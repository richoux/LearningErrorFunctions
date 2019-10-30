#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr_inactive_unit : public Constraint
{
	double required_cost() const override;

public:
	Ctr_inactive_unit( const vector< reference_wrapper<Variable> >& weights );
};
