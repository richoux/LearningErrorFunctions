#include "all-diff.hpp"

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables)
{ }

double AllDiff::required_cost() const
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < variables.size() ; ++i )
		if( !bitvec[ variables[i].get().get_value() ] )
			bitvec[ variables[i].get().get_value() ] = true;
		else
			return 1;
	
	return 0;
}
