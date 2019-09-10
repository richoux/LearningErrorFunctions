#include <iostream>

#include <random>
#include <cmath>

#include "../latin/latin.hpp"
#include "../utils/randutils.hpp"

#include "random_draw.hpp"

// AllDiff concept 
#if defined LATIN
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
#else
bool alldiff_concept( const vector< Variable >& variables )
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < variables.size() ; ++i )
		if( !bitvec[ variables[i].get_value() ] )
			bitvec[ variables[i].get_value() ] = true;
		else
			return false;
	
	return true;
}
#endif


vector< vector<int> > random_draw( const vector< Variable >& variables )
{

#if defined LATIN
	LHS latin;
#endif

	unsigned int counter = 0;
  int value;
  int domain_size = (int)variables[0].get_domain_size();
  int nb_vars = (int)variables.size();

#if not defined LATIN
  vector<int> configuration( nb_vars );
#endif
	vector< vector<int> > samples;

  unsigned long long int one_percent = static_cast<unsigned long long int>( std::pow( domain_size, nb_vars ) / 100 );
  //cout << "1% -> " << one_percent << "\n";
  
#if defined LATIN
  auto latin_draws = latin.sample( variables );

  for( unsigned long long int i = 0; i < one_percent; i += domain_size )
#else
	for( unsigned long long int i = 0; i < one_percent; ++i )
#endif
  {
#if defined LATIN
	  for( auto& sample : latin_draws )
		  if( alldiff_concept( sample ) )
		  {
			  ++counter;
			  samples.push_back( sample );
		  }
	  latin_draws = latin.sample( variables, gen );
#else
	  for( auto& var : variables )
		  var.pick_random_value();

	  if( alldiff_concept( variables ) )
	  {
		  ++counter;
		  for( int i = 0; i < nb_vars; ++i )
			  configuration[i] = variables[i].get_value();
		  samples.push_back( configuration );
	  }
#endif
  }

  // cout << "Density of solutions: " << ( static_cast<double>(counter) * 100 ) / one_percent << "%\n";
  
  return samples;
}
