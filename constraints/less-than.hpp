#pragma once

#include "concept.hpp"

class LessThan : public Concept
{
public:
	LessThan( const vector< reference_wrapper<Variable> >& variables );

	bool concept_( const vector<int>& var ) const override;
};
