#include "concept.hpp"

// AllDiff concept 
bool concept( const vector<int>& var )
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( var.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < var.size() ; ++i )
		if( !bitvec[ var[i] ] )
			bitvec[ var[i] ] = true;
		else
			return false;
	
	return true;
}
