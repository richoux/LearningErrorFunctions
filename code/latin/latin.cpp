#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// We assume that the domain of each variable is the same and starts at 0
vector<int> LHS::sample( int nb_vars, int var_max_value ) const
{
	int value_size = var_max_value + 1;
	vector<int> domains( nb_vars * value_size );
	for( int i = 0; i < nb_vars; ++i )
	{
		std::iota( domains.begin() + i * value_size,
		           domains.begin() + ( i + 1 ) * value_size,
		           0 );
		_rng.shuffle( domains.begin() + i * value_size, domains.begin() + ( i + 1 ) * value_size );		
	}

	vector<int> samples( nb_vars * value_size );
	
	for( int val = 0; val < value_size; ++val )
		for( int var = 0; var < nb_vars; ++var )
			samples[val*nb_vars + var] = domains[var*value_size + val];

	return samples;
}
