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
	double max_cost;

	Concept( int nb_vars, int max_value );
	
	bool concept( const vector<int>& var ) const;
	virtual bool concept( const vector<int>& var, int start, int end ) const = 0;
	virtual bool concept( const vector< reference_wrapper<Variable> >& var ) const = 0;
};
