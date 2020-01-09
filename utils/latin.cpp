#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// LHS::LHS() : _rd(), _rng_std( std::mt19937( _rd() ) ) {}

// We assume that the domain of each variable is the same and starts at 1
vector<int> LHS::sample( int nb_vars, int var_max_value ) const
{
	//_rng_std.seed( _rd() );
		
	vector<int> domains( nb_vars * var_max_value );
	for( int i = 0; i < nb_vars; ++i )
	{
		std::iota( domains.begin() + i * var_max_value,
		           domains.begin() + ( i + 1 ) * var_max_value,
		           1 );
		// randutils version
		_rng.shuffle( domains.begin() + i * var_max_value, domains.begin() + ( i + 1 ) * var_max_value );
		// std version
		//std::shuffle( domains.begin() + i * var_max_value, domains.begin() + ( i + 1 ) * var_max_value, _rng_std );
	}

	vector<int> samples( nb_vars * var_max_value );
	
	// for( int var = 0; var < nb_vars; ++var )
	// 	for( int val = 0; val < var_max_value; ++val )
	// 		samples[val*nb_vars + var] = domains[var*var_max_value + val];

	for( int val = 0; val < var_max_value; ++val )
		for( int var = 0; var < nb_vars; ++var )
			samples[val*nb_vars + var] = domains[var*var_max_value + val];

	return samples;
}
