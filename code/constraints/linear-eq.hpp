#pragma once

#include "concept.hpp"

class LinearEq : public Concept
{
	int _right_value;

public:
	LinearEq( const vector< reference_wrapper<Variable> >& variables, int rv );

	bool concept( const vector<int>& var ) const override;
};
