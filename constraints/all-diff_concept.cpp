#include "all-diff_concept.hpp"

AllDiffConcept::AllDiffConcept( int nb_vars, int max_value )
	: Concept( nb_vars, max_value )
{ }

AllDiffConcept::AllDiffConcept()
	: Concept( 0, 0 )
{ }

bool AllDiffConcept::concept( const vector<int>& var, int start, int end ) const
{
	// We assume our k variables can take values in [1, k]
	vector<bool> bitvec( var.size(), false );

	// Returns false if and only if we have two variables sharing the same value, 
	for( int i = start ; i < end ; ++i )
		if( !bitvec[ var[i]-1 ] )
			bitvec[ var[i]-1 ] = true;
		else
			return false;
	
	return true;	
}

bool AllDiffConcept::concept( const vector< reference_wrapper<Variable> >& var ) const
{
	// We assume our k variables can take values in [1, k]
	vector<bool> bitvec( var.size(), false );

	// Returns false if and only if we have two variables sharing the same value, 
	int value;
	
	for( int i = 0 ; i < var.size() ; ++i )
	{
		value = var[i].get().get_value() - 1;
		if( !bitvec[ value ] )
			bitvec[ value ] = true;
		else
			return false;
	}
	
	return true;	
}
