#pragma once

#include <vector>

#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

class Concept
{
public:
	int nb_vars;
	int max_value;
	double max_error;

	Concept( int nb_vars, int max_value );
	
	bool concept_( const std::vector<int>& var ) const;
	virtual bool concept_( const std::vector<int>& var, int start, int end ) const = 0;
	virtual bool concept_( const std::vector< Variable >& var ) const = 0;
};
