#include <algorithm>

#include "all-diff.hpp"

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables)
{ }

// // AllDiff concept
// double AllDiff::required_cost() const
// {
// 	// We assume our k variables can take values in [0, k-1]
// 	vector<bool> bitvec( variables.size(), false );

// 	// If we have two variables sharing the same value, return 1 (not a solution)
// 	// otherwise, return 0.
// 	for( int i = 0 ; i < variables.size() ; ++i )
// 		if( !bitvec[ variables[i].get().get_value() ] )
// 			bitvec[ variables[i].get().get_value() ] = true;
// 		else
// 			return 1;
	
// 	return 0;
// }

// // SOFT_ALLDIFF cost function (Petit et al. 2001)
// double AllDiff::required_cost() const
// {
// 	double counter = 0;
	
// 	for( int i = 0 ; i < variables.size() - 1 ; ++i )
// 		for( int j = i + 1 ; j < variables.size() ; ++j )
// 			if( variables[i].get().get_value() == variables[j].get().get_value() )
// 				++counter;

// 	return counter;
// }

// Handmade
double AllDiff::required_cost() const
{
	double counter = 0;
	int occurences;
	
	for( int i = 0; i < variables[0].get().get_domain_size(); ++i )
	{
		occurences = std::count_if( variables.begin(), variables.end(), [&](auto v){ return v.get().get_value() == i; } );
		if( occurences > 1 )
			counter += occurences;
	}

	return counter;
}

