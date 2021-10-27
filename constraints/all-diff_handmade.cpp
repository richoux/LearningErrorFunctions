#include <cmath>
#include <algorithm>

#include <iostream>

#include "all-diff_handmade.hpp"

double binomial_with_2( int value )
{
	if( value % 2 == 0 )
		return static_cast<double>( value - 1 ) * ( value / 2 );
	else
		return static_cast<double>( value ) * ( ( value - 1 ) / 2 );
}


AllDiff::AllDiff( const vector<int>& index )
	: Constraint( index ),
	  _count( vector<int>( index.size() ) ),
	  _values( vector<int>( index.size() ) )
{ }

// SOFT_ALLDIFF cost function (Petit et al. 2001)
double AllDiff::required_error( const vector<Variable*>& variables ) const
{
	double counter = 0;

	std::transform( variables.begin(),
	                variables.end(),
	                _values.begin(),
	                []( const auto& v ){ return v->get_value(); } );

	std::fill( _count.begin(), _count.end(), 0 );

	for( auto v : _values )
		++_count[v-1];
	
	for( auto c : _count )
		if( c > 1 )
			counter += binomial_with_2( c );
	
	return counter;
}
