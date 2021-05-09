#include <algorithm>

#include "less-than.hpp"

LessThan::LessThan( const vector< reference_wrapper<Variable> >& variables )
	: Concept( variables, { 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 } ) // all-diff weights
{ }

bool LessThan::concept_( const vector<int>& var ) const
{
	for( int i = 0 ; i < var.size() - 1 ; ++i )
		if( var[i] >= var[i+1] )
			return false;
	
	return true;
}



