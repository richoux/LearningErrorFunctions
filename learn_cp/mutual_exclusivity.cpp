#include <cmath>
#include <algorithm>

#include "mutial_exclusivity.hpp"


MutualExclusivity::MutualExclusivity( const vector<int>& variables )
	: Constraint( variables ),
	  _current_diff( 0 )
{ }

MutualExclusivity::MutualExclusivity( vector<int>&& variables )
	: Constraint( std::move( variables ) ),
	  _current_diff( 0 )
{ }

double MutualExclusivity::required_error( const vector<Variable*>& variables ) const
{
	int sum = 0;
	
	for( auto& v : variables )
		sum += v->get_value();

	_current_diff = sum - 1;

	return std::abs( _current_diff );
}

double MutualExclusivity::optional_delta_error( const vector<Variable*>& variables,
                                                const vector<int>& variable_indexes,
                                                const vector<int>& candidate_values ) const
{
	int diff = _current_diff;

	for( int i = 0 ; i < static_cast<int>( variable_indexes.size() ); ++i )
		diff += ( candidate_values[ i ] - variables[ variable_indexes[i] ]->get_value() );
	
	return std::abs( diff ) - std::abs( _current_diff );
} 

void MutualExclusivity::conditional_update_data_structures( const vector<Variable*>& variables, int variable_index, int new_value ) 
{
	_current_diff += ( new_value - variables[ variable_index ]->get_value() );
}
