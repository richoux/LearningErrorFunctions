#pragma once

#include "concept.hpp"

class AllDiff : public Concept
{
	// double required_cost() const override;

public:
	AllDiff( const vector< reference_wrapper<Variable> >& variables );

	bool concept( const vector<int>& var ) const override;
};
