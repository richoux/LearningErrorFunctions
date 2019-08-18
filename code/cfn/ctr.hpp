#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Ctr : public Constraint
{
	double required_cost() const override;

public:
	Ctr( const vector< reference_wrapper<Variable> >& variables );
};
