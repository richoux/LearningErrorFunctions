#include <cmath>
#include <algorithm>

#include "linear-leq_hardcoded.hpp"


LinearLeq::LinearLeq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _max_value( max_value ),
	  _rhs( rhs )
{ }

double LinearLeq::required_error( const vector<Variable*>& variables ) const
{
	double sum = 0.;
	
	for( auto& v : variables )
		sum += v->get_value();

	return std::max( 0., sum - _rhs );
}
