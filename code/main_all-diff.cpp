#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "all-diff.hpp"
#include "metrics.hpp"
#include "increment.hpp"
#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

#define NB_ALLDIFF 8

int main( int argc, char **argv )
{
	// Create NB_ALLDIFF variables
	vector<Variable> variables;
	for( int i = 0 ; i < NB_ALLDIFF ; ++i )
		variables.push_back( Variable( "v"+i, "v"+i, 0, NB_ALLDIFF ) );

	vector<reference_wrapper<Variable>> variables_ref( variables.begin(), variables.end() );

	// Initialize all variables to 0
	for( auto &var : variables_ref )
		var.set_value( 0 );

	vector<Variable> backup( variables.size() );
	
	// Create the all-different constraint
	shared_ptr<Constraint>alldiff = make_shared<AllDiff>( variables_ref );

	// Big f*cking loop
	// while all variable values are equal to NB_ALLDIFF - 1
	while( std::all_of( variables_ref.begin(),
	                    variables_ref.end(),
	                    [](auto &var){ return var.get_value() == NB_ALLDIFF - 1; } ) )
	{
		// backup since metrics need to change variables value.
		std::copy( variables_ref.begin(), variables_ref.end(), backup.begin() );
		
		for( auto &var : variables_ref )
			cout << var.get_value() << " ";
		cout << ":= " << manhattan( alldiff, variables_ref ) << "\n";

		// roll-back
		for( int i = 0 ; int i < backup.size() ; ++i )
			variables_ref[ i ].set_value( backup[ i ].get_value() );
		
		increment( variables_ref, NB_ALLDIFF );
	}
	
	return EXIT_SUCCESS;
}
