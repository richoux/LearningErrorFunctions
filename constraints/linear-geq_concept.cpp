#include <algorithm>

#include "linear-geq_concept.hpp"

LinearGeqConcept::LinearGeqConcept( int nb_vars, int max_value, int rhs )
	: Concept( nb_vars, max_value ),
	  _rhs( rhs )
{ }

LinearGeqConcept::LinearGeqConcept( int rhs )
	: Concept( 0, 0 ),
	  _rhs( rhs )	  
{ }

bool LinearGeqConcept::concept_( const vector<int>& var, int start, int end ) const
{
	return accumulate( var.begin() + start, var.begin() + end, 0 ) >= _rhs;
}

bool LinearGeqConcept::concept_( const vector<Variable*>& var ) const
{
	int sum = 0;
	
	for( auto& v : var )
		sum += v->get_value();
	
	return sum >= _rhs;	
}
