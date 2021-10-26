#include <cmath>
#include <algorithm>

#include "linear-geq_hardcoded.hpp"


LinearGeq::LinearGeq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _max_value( max_value ),
	  _rhs( rhs )
{ }

LinearGeq::LinearGeq( vector<int>&& variables, int max_value, int rhs )
	: Constraint( std::move( variables ) ),
	  _max_value( max_value ),
	  _rhs( rhs )
{ }

double LinearGeq::required_error( const vector<Variable*>& variables ) const
{
	double sum = 0.;
	
	for( auto& v : variables )
		sum += v->get_value();

	return std::max( 0., _rhs - sum );
}
