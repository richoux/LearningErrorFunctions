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


AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _count( vector<int>( variables.size() ) ),
	  _values( vector<int>( variables.size() ) )
{ }

// SOFT_ALLDIFF cost function (Petit et al. 2001)
double AllDiff::required_cost() const
{
	double counter = 0;

	std::transform( variables.begin(),
	                variables.end(),
	                _values.begin(),
	                []( const auto& v ){ return v.get().get_value(); } );

	std::fill( _count.begin(), _count.end(), 0 );

	for( auto v : _values )
		++_count[v-1];
	
	for( auto c : _count )
		if( c > 1 )
			counter += binomial_with_2( c );

	// for( int i = 0 ; i < variables.size() - 1 ; ++i )
	// 	for( int j = i + 1 ; j < variables.size() ; ++j )
	// 		if( variables[i].get().get_value() == variables[j].get().get_value() )
	// 			++counter;
	
	return counter;
}
