#include <algorithm>

#include "linear-leq_concept.hpp"

LinearLeqConcept::LinearLeqConcept( int nb_vars, int max_value, int rhs )
	: Concept( nb_vars, max_value ),
	  _rhs( rhs )
{ }

LinearLeqConcept::LinearLeqConcept( int rhs )
	: Concept( 0, 0 ),
	  _rhs( rhs )	  
{ }

bool LinearLeqConcept::concept_( const vector<int>& var, int start, int end ) const
{
	return accumulate( var.begin() + start, var.begin() + end, 0 ) <= _rhs;
}

bool LinearLeqConcept::concept_( const vector<Variable*>& var ) const
{
	int sum = 0;
	
	for( auto& v : var )
		sum += v->get_value();
	
	return sum <= _rhs;	
}
