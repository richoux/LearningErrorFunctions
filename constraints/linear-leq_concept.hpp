#pragma once

#include "concept.hpp"

class LinearLeqConcept : public Concept
{
	int _rhs;
	
public:
	LinearLeqConcept( int nb_vars, int max_value, int rhs );
	LinearLeqConcept( int rhs );
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector<Variable*>& var ) const override;
};
