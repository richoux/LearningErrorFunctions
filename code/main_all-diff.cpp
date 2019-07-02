#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

#include "all-diff.hpp"
#include "metrics.hpp"
#include "increment.hpp"
#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

#define NB_ALLDIFF 5

int main( int argc, char **argv )
{
	cout << "Number of variables for AllDiff: " << NB_ALLDIFF << "\n\n";
	
	// Create NB_ALLDIFF variables
	vector<Variable> variables;
	for( int i = 0 ; i < NB_ALLDIFF ; ++i )
		variables.push_back( Variable( std::string("v"+i), std::string("v"+i), 0, NB_ALLDIFF ) );

	vector<reference_wrapper<Variable>> variables_ref( variables.begin(), variables.end() );

	// Initialize all variables to 0
	for( auto var : variables_ref )
		var.get().set_value( 0 );

	vector<int> backup( variables.size() );
	
	// Create the all-different constraint
	shared_ptr<Constraint>alldiff = make_shared<AllDiff>( variables_ref );

	for( auto var : variables_ref )
		cout << var.get().get_value() << " ";
	cout << ":= " << manhattan( alldiff, variables_ref, NB_ALLDIFF ) << "\n";

	// Re-initialize all variables to 0
	for( auto var : variables_ref )
		var.get().set_value( 0 );
	
	// Big f*cking loop
	// while all variable values are not equal to NB_ALLDIFF - 1
	while( !std::all_of( variables_ref.begin(),
	                     variables_ref.end(),
	                     [](auto var){ return var.get().get_value() == NB_ALLDIFF - 1; } ) )
	{
		increment( variables_ref, NB_ALLDIFF );

		// backup since metrics need to change variables value.
		std::transform( variables_ref.begin(),
		                variables_ref.end(),
		                backup.begin(),
		                [](auto var){ return var.get().get_value(); } );

		for( auto var : variables_ref )
			cout << var.get().get_value() << " ";
		cout << ":= " << manhattan( alldiff, variables_ref, NB_ALLDIFF ) << "\n";

		// roll-back
		for( int i = 0 ; i < backup.size() ; ++i )
			variables_ref[ i ].get().set_value( backup[ i ] );		
	};

	return EXIT_SUCCESS;
}
