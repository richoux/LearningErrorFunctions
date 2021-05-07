#pragma once

#include "concept.hpp"

class Overlap1DConcept : public Concept
{
	vector<double> _params;
	
public:
	Overlap1DConcept( int nb_vars, int max_value, vector<double> params );
	Overlap1DConcept( vector<double> params );
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector< reference_wrapper<Variable> >& var ) const override;
};
