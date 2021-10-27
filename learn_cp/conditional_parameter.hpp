#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class ConditionalParameter : public Constraint
{
	bool _has_parameter;
	mutable int _sum;
		
	double required_error( const vector<Variable*>& variables ) const override;

	double optional_delta_error( const vector<Variable*>& variables,
	                             const vector<int>& variable_indexes,
	                             const vector<int>& candidate_values ) const override;

	void conditional_update_data_structures( const vector<Variable*>& variables, int variable_id, int new_value ) override;

public:
	ConditionalParameter( const vector<int>& variables, bool has_parameter );
	ConditionalParameter( vector<int>&& variables, bool has_parameter );
};
