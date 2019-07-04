#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

#include "less_than.hpp"
#include "metrics.hpp"
#include "increment.hpp"
#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

int main( int argc, char **argv )
{
	int nb_vars;
	if( argc <= 1 )
		nb_vars = 3;
	else
		nb_vars = std::stoi( string( argv[1] ) );

	cout << "Number of variables for LessThan: " << nb_vars << "\n\n";

	// Create nb_vars variables
	vector<Variable> variables;
	for( int i = 0 ; i < nb_vars ; ++i )
		variables.push_back( Variable( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, (int)( nb_vars * 1.5 ) ) );

	vector<reference_wrapper<Variable>> variables_ref( variables.begin(), variables.end() );

	// Initialize all variables to 0
	for( auto var : variables_ref )
		var.get().set_value( 0 );

	vector<int> backup( variables.size() );

	// Create the all-different constraint
	shared_ptr<Constraint>lessthan = make_shared<LessThan>( variables_ref );

	for( auto var : variables_ref )
		cout << var.get().get_value() << " ";
	cout << "\nManhattan := " << manhattan( lessthan, variables_ref )
	     << "\nHamming := " << hamming( lessthan, variables_ref )
	     << "\nMix := " << man_ham( lessthan, variables_ref ) << "\n\n";

	// Re-initialize all variables to 0
	for( auto var : variables_ref )
		var.get().set_value( 0 );

	// Big f*cking loop
	// while all variable values are not equal to max_value
	while( !std::all_of( variables_ref.begin(),
	                     variables_ref.end(),
	                     [&](auto var){ return var.get().get_value() == var.get().get_domain_max_value(); } ) )
	{
		increment( variables_ref );

		// backup since metrics need to change variables value.
		std::transform( variables_ref.begin(),
		                variables_ref.end(),
		                backup.begin(),
		                [](auto var){ return var.get().get_value(); } );

		for( auto var : variables_ref )
			cout << var.get().get_value() << " ";
		cout << "\nManhattan := " << manhattan( lessthan, variables_ref )
		     << "\nHamming := " << hamming( lessthan, variables_ref )
		     << "\nMix := " << man_ham( lessthan, variables_ref ) << "\n\n";

		// roll-back
		for( int i = 0 ; i < backup.size() ; ++i )
			variables_ref[ i ].get().set_value( backup[ i ] );
	};

	return EXIT_SUCCESS;
}
