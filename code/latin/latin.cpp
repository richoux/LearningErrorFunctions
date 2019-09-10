#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// We assume that the domain of each variable starts at 0
vector< vector<int> > LHS::sample( const vector< Variable >& variables ) const
{
	auto max = std::max_element( variables.begin(), variables.end(), [](auto& v1, auto& v2){ return v1.get_domain_max_value() < v2.get_domain_max_value(); } );
	return sample( (int)variables.size(), max->get_domain_max_value() );
}

// We assume that the domain of each variable starts at 0
vector< vector<int> > LHS::sample( const vector< reference_wrapper<Variable> >& variables ) const
{
	// vector< Variable > vars;
	// std::transform( variables.begin(), variables.end(), std::back_inserter( vars ), []( auto& v ){ return v.get(); } );

	// return sample( vars );

	auto max = std::max_element( variables.begin(), variables.end(), [](auto& v1, auto& v2){ return v1.get().get_domain_max_value() < v2.get().get_domain_max_value(); } );
	return sample( (int)variables.size(), max->get().get_domain_max_value() );
}

// We assume that the domain of each variable is the same and starts at 0
vector< vector<int> > LHS::sample( int nb_vars, int var_max_value ) const
{
	vector< vector<int> > domains( nb_vars );
	for( int i = 0; i < nb_vars; ++i )
	{
		vector<int> v_domain( var_max_value + 1 );
		// we assume domains start by 0 and contain all numbers from 0 to var_max_value
		std::iota( v_domain.begin(), v_domain.end(), 0 );
		_rng.shuffle( v_domain );		
		domains[ i ] = v_domain;
	}

	TwoDPivotWrapper< vector< vector<int> > > pivot_domains( domains );
	vector< vector<int> > samples( var_max_value + 1 );
	
	for( int s = 0; s < var_max_value + 1; ++s )
	{
		samples[s] = vector<int>( nb_vars );
		for( int v = 0; v < nb_vars; ++v )
			samples[s][v] = pivot_domains[s][v];
	}

	return samples;
}
