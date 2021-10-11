#include "connection-min-gt_concept.hpp"

ConnectionMinGTConcept::ConnectionMinGTConcept( int nb_vars, int max_value, double param )
	: Concept( nb_vars, max_value ),
	  _param( param )
{ }

ConnectionMinGTConcept::ConnectionMinGTConcept( double param )
	: Concept( 0, 0 ),
	  _param( param )
{ }

bool ConnectionMinGTConcept::concept_( const vector<int>& var, int start, int end ) const
{
	return *(std::min_element( var.begin() + start, var.begin() + start + end )) >= _param;
}

bool ConnectionMinGTConcept::concept_( const vector<Variable*>& var ) const
{
	return (*std::min_element( var.begin(),
	                           var.end(),
	                           [](const auto& v1, const auto& v2){ return v1->get_value() < v2->get_value(); } ))->get_value() >= _param;
}
