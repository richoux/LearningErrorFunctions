#include <map>
#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// We assume that the domain of each variable starts at 0
vector< vector<int> > LHS( const vector< reference_wrapper<ghost::Variable> >& variables )
{
	map< int, vector<int> > domains;
	for( auto v : variables )
	{
		vector<int> v_domain( v.get().get_domain_size() );
		// we assume domains start by 0 and contain all numbers from 0 to domain_size-1
		std::iota( v_domain.begin(), v_domain.end(), 0 );
		domains[ v.get().get_id() ] = v_domain;
	}

	std::random_device rd;
	std::mt19937 gen( rd() );

	//int min_domain_size = find( variables.begin(), variables.end(), ...)
	vector< vector<int> > samplings( variables[0].get().get_domain_size() );
	
	for( int s = 0; s < variables[0].get().get_domain_size(); ++s )
	{
		vector<int> sample( variables.size() );

		for( int v = 0; v < variables.size(); ++v )
		{
			uniform_int_distribution<> unif( 0, domains[ variables[v].get().get_id() ].size() - 1 );
			auto &vec = domains[ variables[v].get().get_id() ];
			sample[v] = vec[unif( gen )];
			vec.erase( find( vec.begin(), vec.end(), sample[v] ) );			
		}

		samplings[s] = sample;
	}

	return samplings;
}

// We assume that the domain of each variable is the same and starts at 0
vector< vector<int> > LHS( int nb_vars, int var_max_value )
{
	map< int, vector<int> > domains;
	for( int i = 0; i < nb_vars; ++i )
	{
		vector<int> v_domain( var_max_value + 1 );
		// we assume domains start by 0 and contain all numbers from 0 to var_max_value
		std::iota( v_domain.begin(), v_domain.end(), 0 );
		domains[ i ] = v_domain;
	}

	std::random_device rd;
	std::mt19937 gen( rd() );

	//int min_domain_size = find( variables.begin(), variables.end(), ...)
	vector< vector<int> > samplings( var_max_value + 1 );
	
	for( int s = 0; s < var_max_value + 1; ++s )
	{
		vector<int> sample( nb_vars );

		for( int v = 0; v < nb_vars; ++v )
		{
			uniform_int_distribution<> unif( 0, domains[ v ].size() - 1 );
			auto &vec = domains[ v ];
			sample[v] = vec[unif( gen )];
			vec.erase( find( vec.begin(), vec.end(), sample[v] ) );			
		}

		samplings[s] = sample;
	}

	return samplings;
}
