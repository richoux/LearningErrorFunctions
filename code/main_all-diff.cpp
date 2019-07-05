#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

#include "all-diff.hpp"
#include "metrics.hpp"
#include "increment.hpp"
#include "print_csv.hpp"
#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

int main( int argc, char **argv )
{
	int nb_vars;
	if( argc <= 1 )
		nb_vars = 4;
	else
		nb_vars = std::stoi( string( argv[1] ) );

	// cout << "Number of variables for AllDiff: " << nb_vars << "\n\n";

	// Create nb_vars variables
	vector<Variable> variables;
	for( int i = 0 ; i < nb_vars ; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, nb_vars );

	vector<reference_wrapper<Variable>> variables_ref( variables.begin(), variables.end() );

	// Initialize all variables to 0
	for( auto var : variables_ref )
		var.get().set_value( 0 );

	vector<int> backup( variables.size() );

	// Create the all-different constraint
	shared_ptr<Constraint>alldiff = make_shared<AllDiff>( variables_ref );

	cout << "Hamming,Manhattan,Mix";
	for( auto var : variables_ref )
		cout << "," << var.get().get_name();
	cout << "\n";

	print_csv( variables_ref,
	           hamming( alldiff, variables_ref ),
	           manhattan( alldiff, variables_ref ),
	           ham_man( alldiff, variables_ref ) );
	
	// for( auto var : variables_ref )
	// 	cout << var.get().get_value() << " ";
	// cout << "\nHamming := " << hamming( alldiff, variables_ref )
	//      << "\nManhattan := " << manhattan( alldiff, variables_ref )
	//      << "\nMix := " << ham_man( alldiff, variables_ref ) << "\n\n";

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

		print_csv( variables_ref,
		           hamming( alldiff, variables_ref ),
		           manhattan( alldiff, variables_ref ),
		           ham_man( alldiff, variables_ref ) );
		
		// for( auto var : variables_ref )
		// 	cout << var.get().get_value() << " ";
		// cout << "\nHamming := " << hamming( alldiff, variables_ref )
		//      << "\nManhattan := " << manhattan( alldiff, variables_ref )
		//      << "\nMix := " << ham_man( alldiff, variables_ref ) << "\n\n";

		// roll-back
		for( int i = 0 ; i < backup.size() ; ++i )
			variables_ref[ i ].get().set_value( backup[ i ] );
	};

	return EXIT_SUCCESS;
}
