#include <cmath>
#include <algorithm>

#include "conditional_parameter.hpp"


ConditionalParameter::ConditionalParameter( const vector<int>& variables, bool has_parameter )
	: Constraint( variables ),
	  _has_parameter( has_parameter ),
	  _sum( 0 )
{ }

ConditionalParameter::ConditionalParameter( vector<int>&& variables, bool has_parameter )
	: Constraint( std::move( variables ) ),
	  _has_parameter( has_parameter ),
	  _sum( 0 )
{ }

double ConditionalParameter::required_error( const vector<Variable*>& variables ) const
{
	_sum = 0;
	for( auto& var : variables )
		_sum += var->get_value();
			
	if( _has_parameter )
	{
		if( _sum == 0 )
			return 1.0;
		else
			return 0.0;
	}
	else
		return _sum;
}

double ConditionalParameter::optional_delta_error( const vector<Variable*>& variables,
                                                const vector<int>& variable_indexes,
                                                const vector<int>& candidate_values ) const
{
	int diff = _sum;

	for( int i = 0 ; i < static_cast<int>( variable_indexes.size() ); ++i )
		diff += ( candidate_values[ i ] - variables[ variable_indexes[i] ]->get_value() );
	
	if( _has_parameter )
	{
		if( _sum == 0 && diff > 0 )
			return -1.0;
		else
			if( _sum > 0 && diff == 0 )
				return 1.0;
			else
				return 0.0;
	}
	else
		return diff - _sum;
} 

void ConditionalParameter::conditional_update_data_structures( const vector<Variable*>& variables, int variable_index, int new_value ) 
{
	_sum += ( new_value - variables[ variable_index ]->get_value() );
}
