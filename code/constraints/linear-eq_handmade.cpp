#include <cmath>
#include <algorithm>

#include "linear-eq_handmade.hpp"


LinearEq::LinearEq( const vector< reference_wrapper<Variable> >& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _max_value( max_value ),
	  _rhs( rhs )
{
	// we consider all variables start from value 1
	int diff_min_val = std::abs( _rhs - (int)variables.size() );
	int diff_max_val = std::abs( _rhs - ( _max_value * (int)variables.size() ) );
	
	_max_diff = std::max( diff_min_val, diff_max_val );
}

double LinearEq::required_cost() const
{
	int sum = 0;
	
	for( auto& v : variables )
		sum += v.get().get_value();

	int diff = std::abs( _rhs - sum );

	if( diff == 0 )
		return 0.;
	
	int number_var_to_change = ( diff / _max_value ) + 1;
		
	double decimals = 0.9 * ( static_cast<double>( diff ) / _max_diff );

	return number_var_to_change + decimals;
}
