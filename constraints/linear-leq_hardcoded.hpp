#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class LinearLeq : public Constraint
{
	int _max_value;
	int _rhs;
	int _max_diff;
	
	double required_error( const vector<Variable*>& variables ) const override;

public:
	LinearLeq( const vector<int>& variables, int max_value, int rhs );
	LinearLeq( vector<int>&& variables, int max_value, int rhs );
};
