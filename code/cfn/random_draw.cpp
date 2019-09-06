#include <iostream>

#include <vector>
#include <random>
#include <cmath>

#include <ghost/variable.hpp>
#include "latin.hpp"

using namespace ghost;
using namespace std;

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

int main( int argc, char** argv )
{
	int nb_vars;
	if( argc == 1 )
		nb_vars = 9;
	else
	{
		nb_vars = std::stoi( argv[1] );
		nb_vars *= nb_vars;
	}

	std::random_device rd{};
	std::mt19937 gen{rd()};
#if not defined LATIN
	std::uniform_int_distribution<> uniform{ 0, nb_vars - 1 };
#endif
	
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, nb_vars );

  unsigned int counter = 0;
  int value;
  auto domain_size = variables[0].get_domain_size();
  
  unsigned long long int one_percent = static_cast<unsigned long long int>( std::pow( domain_size, nb_vars ) / 100 );
  //cout << "1% -> " << one_percent << "\n";
  
  auto latin_draws = LHS( variables, gen );
  
#if defined LATIN
  for( unsigned long long int i = 0; i < one_percent; i += domain_size )
#else
	for( unsigned long long int i = 0; i < one_percent; ++i )
#endif
  {
#if defined LATIN
	  for( auto& sample : latin_draws )
		  if( alldiff_concept( sample ) )
			  ++counter;
	  latin_draws = LHS( variables, gen );
#else
	  for( auto& var : variables )
	  {
		  value = uniform( gen );
		  var.set_value( value );
		  //cout << value << " ";
	  }
	  //cout << "\n";

	  if( alldiff_concept( variables ) )
		  ++counter;
#endif
  }

  cout << "Density of solutions: " << ( static_cast<double>(counter) * 100 ) / one_percent << "%\n";
  
  return EXIT_SUCCESS;
}
