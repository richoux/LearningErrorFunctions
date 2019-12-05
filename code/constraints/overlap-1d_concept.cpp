#include <algorithm>

#include "overlap-1d_concept.hpp"

Overlap1DConcept::Overlap1DConcept( int nb_vars, int max_value, vector<double> params )
	: Concept( nb_vars, max_value ),
	  _params( params )
{ }

Overlap1DConcept::Overlap1DConcept( vector<double> params )
	: Concept( 0, 0 ),
	  _params( params )	  
{ }

bool Overlap1DConcept::concept( const vector<int>& var, int start, int end ) const
{
	for( int i = start; i < end; ++i )
		for( int j = start; j < end; ++j )
			if( j != i && var[j] >= var[i] && var[j] <= var[i] + _params[i] )
				return false;

	return true;
}

bool Overlap1DConcept::concept( const vector< reference_wrapper<Variable> >& var ) const
{
	for( int i = 0; i < (int)var.size(); ++i )
		for( int j = 0; i < (int)var.size(); ++j )
			if( j != i
			    &&
			    var[j].get().get_value() >= var[i].get().get_value()
			    &&
			    var[j].get().get_value() <= var[i].get().get_value() + _params[i] )
				return false;

	return true;
}
