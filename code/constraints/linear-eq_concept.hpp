#pragma once

#include "concept.hpp"

class LinearEqConcept : public Concept
{
	int _rhs;
	
public:
	LinearEqConcept( int nb_vars, int max_value, int rhs );
	LinearEqConcept( int rhs );
	
	bool concept( const vector<int>& var, int start, int end ) const override;
	bool concept( const vector< reference_wrapper<Variable> >& var ) const override;
};
