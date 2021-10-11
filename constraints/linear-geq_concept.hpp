#pragma once

#include "concept.hpp"

class LinearGeqConcept : public Concept
{
	int _rhs;
	
public:
	LinearGeqConcept( int nb_vars, int max_value, int rhs );
	LinearGeqConcept( int rhs );
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector<Variable*>& var ) const override;
};
