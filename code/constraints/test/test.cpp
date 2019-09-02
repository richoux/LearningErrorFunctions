#include <iostream>
#include <fstream>
#include <string>

#include <vector>

#include <ghost/variable.hpp>
#include "../all-diff.hpp"
#include "increment.hpp"

using namespace ghost;
using namespace std;

int main( int argc, char** argv )
{
	if( argc == 1 )
		return EXIT_FAILURE;
		
	int nb_vars;
	if( argc == 2 )
		nb_vars = 9;
	else
	{
		nb_vars = std::stoi( argv[2] );
		nb_vars *= nb_vars;
	}

	ofstream file;
	file.open( argv[1] );
	
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, nb_vars );

  vector< reference_wrapper<Variable> > var_ref(  variables.begin(), variables.end() );

  shared_ptr< Constraint > all_diff = make_shared< AllDiff >( var_ref );
  //shared_ptr< Constraint > all_diff = make_shared< AllDiff >( var_ref );

  // start with the 0-vector
  for( auto& var : var_ref )
  {
		var.get().set_value( 0 );
		//cout << "0 ";
		file << "0 ";
  }

  //cout << "-> " << all_diff->cost() << "\n";
  file << "-> " << all_diff->cost() << "\n";

  while( increment( var_ref ) )
  {
	  for( auto& var : var_ref )
		  //cout << var.get().get_value() << " ";
		  file << var.get().get_value() << " ";
	  //cout << "-> " << all_diff->cost() << "\n";
	  file << "-> " << all_diff->cost() << "\n";
  }

  return EXIT_SUCCESS;
}
