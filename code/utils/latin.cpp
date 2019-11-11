#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// We assume that the domain of each variable is the same and starts at 0
vector<int> LHS::sample( int nb_vars, int var_max_value ) const
{
	vector<int> domains( nb_vars * var_max_value );
	for( int i = 0; i < nb_vars; ++i )
	{
		std::iota( domains.begin() + i * var_max_value,
		           domains.begin() + ( i + 1 ) * var_max_value,
		           1 );
		_rng.shuffle( domains.begin() + i * var_max_value, domains.begin() + ( i + 1 ) * var_max_value );		
	}

	vector<int> samples( nb_vars * var_max_value );
	
	for( int val = 0; val < var_max_value; ++val )
		for( int var = 0; var < nb_vars; ++var )
			samples[val*nb_vars + var] = domains[var*var_max_value + val];

	return samples;
}
