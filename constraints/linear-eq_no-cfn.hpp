#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "linear-eq_concept.hpp"

using namespace std;
using namespace ghost;

class LinearEq : public Constraint
{
	int _rhs;
	LinearEqConcept _le_concept_;
	
	double required_error( const vector<Variable*>& variables ) const override;

public:
	LinearEq( const vector<int>& variables, int max_value, int rhs );
};
