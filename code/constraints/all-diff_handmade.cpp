#include <cmath>
#include <algorithm>

#include "all-diff_handmade.hpp"


AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables )
{ }

// SOFT_ALLDIFF cost function (Petit et al. 2001)
double AllDiff::required_cost() const
{
	double counter = 0;
	
	for( int i = 0 ; i < variables.size() - 1 ; ++i )
		for( int j = i + 1 ; j < variables.size() ; ++j )
			if( variables[i].get().get_value() == variables[j].get().get_value() )
				++counter;
	
	return counter;
}
