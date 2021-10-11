#include <cmath>
#include <algorithm>

#include "linear-eq_hardcoded.hpp"


LinearEq::LinearEq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _max_value( max_value ),
	  _rhs( rhs ),
	  _current_diff( 0 )
{ }

double LinearEq::required_error( const vector<Variable*>& variables ) const
{
	int sum = 0;
	
	for( auto& v : variables )
		sum += v->get_value();

	_current_diff = sum - _rhs;
	
	return std::abs( _current_diff );
}

double LinearEq::optional_delta_error( const vector<Variable*>& variables,
                                       const vector<int>& variable_indexes,
                                       const vector<int>& candidate_values ) const
{
	int diff = _current_diff;

	for( int i = 0 ; i < static_cast<int>( variable_indexes.size() ); ++i )
		diff += ( candidate_values[ i ] - variables[ variable_indexes[i] ]->get_value() );
	
	return std::abs( diff ) - std::abs( _current_diff );
} 

void LinearEq::conditional_update_data_structures( const vector<Variable*>& variables, int variable_index, int new_value ) 
{
	_current_diff += ( new_value - variables[ variable_index ]->get_value() );
}
