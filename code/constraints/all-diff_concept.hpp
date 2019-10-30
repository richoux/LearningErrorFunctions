#pragma once

#include "concept.hpp"

class AllDiffConcept : public Concept
{
public:
	AllDiffConcept( int nb_vars, int max_value );
	AllDiffConcept();
	
	bool concept( const vector<int>& var, int start, int end ) const override;
	bool concept( const vector< reference_wrapper<Variable> >& var ) const override;
};
