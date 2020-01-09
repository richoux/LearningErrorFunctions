#pragma once

#include <string>

#include "concept.hpp"

#include "../utils/randutils.hpp"

class RandomConcept : public Concept
{
	vector<string> _solutions;
	mutable randutils::mt19937_rng _rng;
	
public:
	RandomConcept( int nb_vars, int max_value );
	RandomConcept();
	
	bool concept( const vector<int>& var, int start, int end ) const override;
	bool concept( const vector< reference_wrapper<Variable> >& var ) const override;
};
