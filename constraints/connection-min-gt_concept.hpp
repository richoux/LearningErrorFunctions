#pragma once

#include "concept.hpp"

// Check if the minimal value is equals to/greater than/less than a given parameter
// Here, we consider that this minimal value must be greater than the parameter
class ConnectionMinGTConcept : public Concept
{
	double _param;
	
public:
	ConnectionMinGTConcept( int nb_vars, int max_value, double param );
	ConnectionMinGTConcept( double param );
	
	bool concept_( const vector<int>& var, int start, int end ) const override;
	bool concept_( const vector<Variable*>& var ) const override;
};
