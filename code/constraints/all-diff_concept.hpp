#pragma once

#include "concept.hpp"

class AllDiffConcept : public Concept
{
public:
	AllDiffConcept( int nb_vars, int max_domain );
	AllDiffConcept();
	
	bool concept( const vector<int>& var ) const override;
	bool concept( const vector< reference_wrapper<Variable> >& var ) const override;
};
