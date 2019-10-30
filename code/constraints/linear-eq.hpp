#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "linear-eq_concept.hpp"

using namespace std;
using namespace ghost;

class LinearEq : public Constraint
{
	vector<int> _weights;
	int _rhs;
	LinearEqConcept _le_concept;
	
	double required_cost() const override;

public:
	LinearEq( const vector< reference_wrapper<Variable> >& variables, int max_value, int rhs );
};
