#include <iostream>

#include <random>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "../latin/latin.hpp"
#include "../utils/randutils.hpp"

#include "random_draw.hpp"

#if defined CHRONO
static bool first = true;
#endif

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

bool alldiff_concept( const vector< int >& variables, int start, int end )
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = start ; i < end ; ++i )
		if( !bitvec[ variables[i] ] )
			bitvec[ variables[i] ] = true;
		else
			return false;
	
	return true;
}

////////////////////////////

// void random_draw( const vector< Variable >& variables, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent )
// {
// 	random_draw( (int)variables.size(), (int)variables[0].get_domain_size() - 1, solutions, not_solutions, percent );
// }

// void random_draw( int nb_vars, int max_value, vector< vector<int> >& solutions, vector< vector<int> >& not_solutions, double percent )
// {
// #if defined CHRONO
// 	auto start = std::chrono::steady_clock::now();
// #endif

// #if defined LATIN
// 	LHS latin;
// #else
// 	randutils::mt19937_rng rng;
// #endif

// 	unsigned int counter = 0;

// #if not defined LATIN
//   vector<int> configuration( nb_vars );
// #endif
//   unsigned long long int sampling_size = static_cast<unsigned long long int>( percent * std::pow( max_value + 1, nb_vars ) / 100 );
//   //cout << "1% -> " << sampling_size << "\n";
  
// #if defined LATIN
//   auto latin_draws = latin.sample( nb_vars, max_value );

//   for( unsigned long long int i = 0; i < sampling_size; i += ( max_value + 1 ) )
// #else
// 	for( unsigned long long int i = 0; i < sampling_size; ++i )
// #endif
//   {
// #if defined LATIN
// 	  for( auto sample : latin_draws )
// 		  if( alldiff_concept( sample ) )
// 		  {
// 			  ++counter;
// 			  solutions.push_back( sample );
// 		  }
// 		  else
// 			  not_solutions.push_back( sample );
			  
// 	  latin_draws = latin.sample( nb_vars, max_value );
// #else
// 	  for( int i = 0; i < nb_vars; ++i )
// 		  configuration[i] = rng.uniform( 0, max_value );

// 	  if( alldiff_concept( configuration ) )
// 	  {
// 		  ++counter;
// 		  solutions.push_back( configuration );
// 	  }
// 	  else
// 		  not_solutions.push_back( configuration );		  
// #endif
//   }

// #if defined CHRONO
// 	if( first )
// 	{
// 		auto end = std::chrono::steady_clock::now();
// 		cerr << "random_draw: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
// 		first = false;
// 	}
// #endif

//   // cout << "Density of solutions: " << ( static_cast<double>(counter) * 100 ) / sampling_size << "%\n";
// }

void random_draw( int nb_vars, int max_value, vector<int>& solutions, vector<int>& not_solutions, double percent )
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif

#if defined LATIN
	LHS latin;
	int value_size = max_value + 1;
#else
	randutils::mt19937_rng rng;
#endif

	//unsigned int counter = 0;

#if not defined LATIN
  vector<int> configuration( nb_vars );
#endif

  unsigned long long int sampling_size = static_cast<unsigned long long int>( percent * std::pow( max_value + 1, nb_vars ) / 100 );
  //cout << "1% -> " << sampling_size << "\n";
  
#if defined LATIN
  vector<int> latin_draws = latin.sample( nb_vars, max_value );

  for( unsigned long long int i = 0; i < sampling_size; i += value_size )
#else
	for( unsigned long long int i = 0; i < sampling_size; ++i )
#endif
  {
#if defined LATIN
	  for( int j = 0; j < value_size; ++j )
		  if( alldiff_concept( latin_draws, j * nb_vars, (j + 1) * nb_vars ) )
		  {
			  //++counter;
			  solutions.insert( solutions.end(),
			                    latin_draws.begin() + ( j * nb_vars ),
			                    latin_draws.begin() + ( ( j + 1 ) * nb_vars ) );
		  }
		  else
			  not_solutions.insert( not_solutions.end(),
			                        latin_draws.begin() + ( j * nb_vars ),
			                        latin_draws.begin() + ( ( j + 1 ) * nb_vars ) );
	  
	  latin_draws = latin.sample( nb_vars, max_value );
#else
	  rng.generate( configuration, 0, max_value );

	  if( alldiff_concept( configuration ) )
	  {
		  //++counter;
		  solutions.insert( solutions.end(), configuration.begin(), configuration.end() );
	  }
	  else
		  not_solutions.insert( not_solutions.end(), configuration.begin(), configuration.end() );
#endif
  }

#if defined CHRONO
	if( first )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "random_draw: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first = false;
	}
#endif

  // cout << "Density of solutions: " << ( static_cast<double>(counter) * 100 ) / sampling_size << "%\n";
}
