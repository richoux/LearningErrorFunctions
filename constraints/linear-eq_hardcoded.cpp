#include <cmath>
#include <algorithm>

#include "linear-eq_hardcoded.hpp"


LinearEq::LinearEq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _max_value( max_value ),
	  _rhs( rhs )
{ }

double LinearEq::required_error( const vector<Variable*>& variables ) const
{
	int sum = 0;
	
	for( auto& v : variables )
		sum += v->get_value();

	return std::abs( sum - _rhs );
}
