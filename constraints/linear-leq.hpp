#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "linear-leq_concept.hpp"

using namespace std;
using namespace ghost;

class LinearLeq : public Constraint
{
	vector<int> _weights;
	int _rhs;
	LinearLeqConcept _le_concept_;
	
	double required_error( const vector<Variable*>& variables ) const override;

public:
	LinearLeq( const vector<int>& variables, int max_value, int rhs );
};
