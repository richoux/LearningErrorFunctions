#include "less-than_concept.hpp"

LessThanConcept::LessThanConcept( int nb_vars, int max_value )
	: Concept( nb_vars, max_value )
{ }

LessThanConcept::LessThanConcept()
	: Concept( 0, 0 )
{ }

bool LessThanConcept::concept( const vector<int>& var, int start, int end ) const
{
	for( int i = start ; i < end - 1 ; ++i )
		if( var[i] > var[i+1] )
			return false;
	
	return true;
}

bool LessThanConcept::concept( const vector< reference_wrapper<Variable> >& var ) const
{
	for( int i = 0 ; i < var.size() - 1 ; ++i )
		if( var[i].get().get_value() > var[i+1].get().get_value() )
			return false;
	
	return true;
}