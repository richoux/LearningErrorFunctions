#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr_dependency : public Constraint
{
	double required_cost() const override;

public:
	Ctr_dependency( const vector< reference_wrapper<Variable> >& weights );
};
