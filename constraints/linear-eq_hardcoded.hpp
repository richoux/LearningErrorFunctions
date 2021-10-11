#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class LinearEq : public Constraint
{
	int _max_value;
	int _rhs;
	int _max_diff;
	mutable int _current_diff;
	
	double required_error( const vector<Variable*>& variables ) const override;

	double optional_delta_error( const vector<Variable*>& variables,
	                             const vector<int>& variable_indexes,
	                             const vector<int>& candidate_values ) const override;

	void conditional_update_data_structures( const vector<Variable*>& variables, int variable_id, int new_value ) override;

public:
	LinearEq( const vector<int>& variables, int max_value, int rhs );
};
