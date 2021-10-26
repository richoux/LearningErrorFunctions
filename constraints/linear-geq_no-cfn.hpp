#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "linear-geq_concept.hpp"

using namespace std;
using namespace ghost;

class LinearGeq : public Constraint
{
	int _rhs;
	LinearGeqConcept _le_concept_;
	
	double required_error( const vector<Variable*>& variables ) const override;

public:
	LinearGeq( const vector<int>& variables, int max_value, int rhs );
	LinearGeq( vector<int>&& variables, int max_value, int rhs );
};
