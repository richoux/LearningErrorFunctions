#pragma once

#include "concept.hpp"

class LinearEqConcept : public Concept
{
	int _rhs;
	
public:
	LinearEqConcept( int nb_vars, int max_value, int rhs );
	LinearEqConcept( int rhs );
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector<Variable*>& var ) const override;
};
