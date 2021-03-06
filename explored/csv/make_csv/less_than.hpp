#pragma once

#include <vector>

#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

using namespace std;
using namespace ghost;

class LessThan : public Constraint
{
	double required_cost() const override;

public:
	LessThan( const vector< reference_wrapper<Variable> >& variables );
};
