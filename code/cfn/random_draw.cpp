#include <iostream>

#include <random>
#include <cmath>

#include "../latin/latin.hpp"
#include "../utils/randutils.hpp"

#include "random_draw.hpp"

// AllDiff concept 
bool alldiff_concept( const vector< int >& variables )
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < variables.size() ; ++i )
		if( !bitvec[ variables[i] ] )
			bitvec[ variables[i] ] = true;
		else
			return false;
	
	return true;
}

void random_draw( const vector< Variable >& variables, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent )
{
	random_draw( (int)variables.size(), (int)variables[0].get_domain_size() - 1, solutions, not_solutions, percent );
}

void random_draw( int nb_vars, int max_value, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent )
{

#if defined LATIN
	LHS latin;
#else
	randutils::mt19937_rng rng;
#endif

	unsigned int counter = 0;

#if not defined LATIN
  vector<int> configuration( nb_vars );
#endif
  unsigned long long int sampling_size = static_cast<unsigned long long int>( percent * std::pow( max_value + 1, nb_vars ) / 100 );
  //cout << "1% -> " << sampling_size << "\n";
  
#if defined LATIN
  auto latin_draws = latin.sample( variables );

  for( unsigned long long int i = 0; i < sampling_size; i += ( max_value + 1 ) )
#else
	for( unsigned long long int i = 0; i < sampling_size; ++i )
#endif
  {
#if defined LATIN
	  for( auto& sample : latin_draws )
		  if( alldiff_concept( sample ) )
		  {
			  ++counter;
			  solutions.push_back( sample );
		  }
		  else
			  not_solutions.push_back( sample );
			  
	  latin_draws = latin.sample( variables, gen );
#else
	  for( int i = 0; i < nb_vars; ++i )
		  configuration[i] = rng.uniform( 0, max_value );

	  if( alldiff_concept( configuration ) )
	  {
		  ++counter;
		  solutions.push_back( configuration );
	  }
	  else
		  not_solutions.push_back( configuration );		  
#endif
  }

  // cout << "Density of solutions: " << ( static_cast<double>(counter) * 100 ) / sampling_size << "%\n";
}
