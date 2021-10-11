#pragma once

#include "concept.hpp"

class AllDiffConcept : public Concept
{
public:
	AllDiffConcept( int nb_vars, int max_value );
	AllDiffConcept();
	
	bool concept_( const std::vector<int>& var, int start, int end ) const override;
	bool concept_( const std::vector<Variable*>& var ) const override;
};
