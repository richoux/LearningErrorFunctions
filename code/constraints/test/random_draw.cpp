#include <iostream>

#include <vector>
#include <random>

#include <ghost/variable.hpp>

using namespace ghost;
using namespace std;

// AllDiff concept 
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
	std::uniform_int_distribution<> uniform{ 0, nb_vars - 1 };
	
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, nb_vars );

  int counter = 0;
  int value;
  for( int i = 0; i < 1000000; ++i )
  {
	  for( auto& var : variables )
	  {
		  value = uniform( gen );
		  var.set_value( value );
		  //cout << value << " ";
	  }
	  //cout << "\n";

	  if( alldiff_concept( variables ) )
		  ++counter;
  }

  cout << "Ratio: " << counter <<  "/1000000\n";
  
  return EXIT_SUCCESS;
}
