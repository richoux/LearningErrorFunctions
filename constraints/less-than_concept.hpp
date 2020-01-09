#pragma once

#include "concept.hpp"

class LessThanConcept : public Concept
{
public:
	LessThanConcept( int nb_vars, int max_value );
	LessThanConcept();
	
	bool concept( const vector<int>& var, int start, int end ) const override;
	bool concept( const vector< reference_wrapper<Variable> >& var ) const override;
};
