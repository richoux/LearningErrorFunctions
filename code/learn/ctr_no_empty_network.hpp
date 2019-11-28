#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr_no_empty_network : public Constraint
{
	double required_cost() const override;

public:
	Ctr_no_empty_network( const vector< reference_wrapper<Variable> >& weights );
};
