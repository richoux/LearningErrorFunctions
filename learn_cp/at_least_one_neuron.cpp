#include <cmath>
#include <algorithm>

#include "at_least_one_neuron.hpp"


AtLeast::AtLeast( const vector<int>& variables )
	: Constraint( variables ),
	  _sum( 0 )
{ }

AtLeast::AtLeast( vector<int>&& variables )
	: Constraint( std::move( variables ) ),
	  _sum( 0 )
{ }

double AtLeast::required_error( const vector<Variable*>& variables ) const
{
	_sum = 0;
	
	for( auto& v : variables )
		_sum += v->get_value();

	if( _sum == 0 )
		return 1.0;
	else
		return 0.0;
}

double AtLeast::optional_delta_error( const vector<Variable*>& variables,
                                                const vector<int>& variable_indexes,
                                                const vector<int>& candidate_values ) const
{
	int diff = _sum;

	for( int i = 0 ; i < static_cast<int>( variable_indexes.size() ); ++i )
		diff += ( candidate_values[ i ] - variables[ variable_indexes[i] ]->get_value() );

	if( _sum == 0 && diff > 0 )
		return -1.0;
	else
		if( _sum > 0 && diff == 0 )
			return 1.0;
		else
			return 0.0;
} 

void AtLeast::conditional_update_data_structures( const vector<Variable*>& variables, int variable_index, int new_value ) 
{
	_sum += ( new_value - variables[ variable_index ]->get_value() );
}
