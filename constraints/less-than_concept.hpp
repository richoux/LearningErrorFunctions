#pragma once

#include "concept.hpp"

class LessThanConcept : public Concept
{
public:
	LessThanConcept( int nb_vars, int max_value );
	LessThanConcept();
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector< Variable >& var ) const override;
};
