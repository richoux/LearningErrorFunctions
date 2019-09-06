#include <map>
#include <numeric>
#include <random>
#include <algorithm>

#include "latin.hpp"

// We assume that the domain of each variable starts at 0
vector< vector<int> > LHS( const vector< Variable >& variables, std::mt19937& gen )
{
	map< int, vector<int> > domains;
	for( auto v : variables )
	{
		vector<int> v_domain( v.get_domain_size() );
		std::iota( v_domain.begin(), v_domain.end(), 0 );
		domains[ v.get_id() ] = v_domain;
	}

	vector< vector<int> > samplings( variables[0].get_domain_size() );
	
	for(int s = 0; s < variables[0].get_domain_size(); ++s )
	{
		vector<int> sample( variables.size() );

		for( int v = 0; v < variables.size(); ++v )
		{
			uniform_int_distribution<> unif( 0, domains[ variables[v].get_id() ].size() - 1 );
			auto &vec = domains[ variables[v].get_id() ];
			sample[v] = vec[unif( gen )];
			vec.erase( find( vec.begin(), vec.end(), sample[v] ) );			
		}

		samplings[s] = sample;
	}

	return samplings;
}

// We assume that the domain of each variable starts at 0
vector< vector<int> > LHS( const vector< reference_wrapper<Variable> >& variables, std::mt19937& gen )
{
	vector< Variable > vars;
	std::transform( variables.begin(), variables.end(), std::back_inserter( vars ), []( auto& v ){ return v.get(); } );

	return LHS( vars, gen );
}

// We assume that the domain of each variable is the same and starts at 0
vector< vector<int> > LHS( int nb_vars, int var_max_value, std::mt19937& gen )
{
	map< int, vector<int> > domains;
	for( int i = 0; i < nb_vars; ++i )
	{
		vector<int> v_domain( var_max_value + 1 );
		// we assume domains start by 0 and contain all numbers from 0 to var_max_value
		std::iota( v_domain.begin(), v_domain.end(), 0 );
		domains[ i ] = v_domain;
	}

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
