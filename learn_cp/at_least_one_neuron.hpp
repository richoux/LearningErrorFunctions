#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class AtLeast : public Constraint
{
	mutable int _sum;
	
	double required_error( const vector<Variable*>& variables ) const override;

	double optional_delta_error( const vector<Variable*>& variables,
	                             const vector<int>& variable_indexes,
	                             const vector<int>& candidate_values ) const override;

	void conditional_update_data_structures( const vector<Variable*>& variables, int variable_id, int new_value ) override;

public:
	AtLeast( const vector<int>& variables );
	AtLeast( vector<int>&& variables );
};
