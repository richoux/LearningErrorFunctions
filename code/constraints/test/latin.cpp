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
