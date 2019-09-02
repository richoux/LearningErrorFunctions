#include <algorithm>

#include "increment.hpp"

/*
 * Local functions
 */

bool increment( const vector<reference_wrapper<Variable>> &variables,
                const int index )
{
	if( index < 0 )
		return false;

	if( variables[ index ].get().get_value() < variables.size() - 1 )
		variables[ index ].get().set_value( variables[ index ].get().get_value() + 1 );
	else
	{
		variables[ index ].get().set_value( 0 );
		increment( variables, index - 1 );
	}

	return true;
}

void increment_some_vars( const vector<reference_wrapper<Variable>> &variables,
                          const vector<int> &vars_index,
                          const int index )
{
	if( index >= vars_index.size() )
		return;

	int current_var_index = vars_index[ index ];

	if( variables[ current_var_index ].get().get_value() < variables.size() - 1 )
		variables[ current_var_index ].get().set_value( variables[ current_var_index ].get().get_value() + 1 );
	else
	{
		variables[ current_var_index ].get().set_value( 0 );
		increment_some_vars( variables, vars_index, index + 1 );
	}
}

void increment_boolean_vector( vector<bool> &vec,
                               const int index )
{
	if( std::all_of( vec.begin(), vec.end(), [](auto b){ return b; } ) )
		return;

	if( !vec[ index] )
		vec[ index ] = true;
	else
	{
		vec[ index ] = false;
		increment_boolean_vector( vec, index + 1 );
	}
}

// shift at the beginning of the vector all Trues between [0, index]
void reset_to_the_left( vector<bool> &vec,
                        std::vector<bool>::iterator index )
{
	if( index <= vec.begin() )
		return;
	
	int number_trues = std::count_if( vec.begin(), index, []( auto b ){ return b; } );
	std::fill( vec.begin(), index, false );
	std::fill( vec.begin(), vec.begin() + number_trues, true );	
}

// shift a True at vec[index] to the right (so at vec[index+1])
void shift_right( vector<bool> &vec,
                  std::vector<bool>::iterator index )
{
	if( index == vec.end() - 1 || !(*index) )
		return;

	if( !(*( index + 1 ) ) )
	{
		(*index) = false;
		*( index + 1 ) = true;
		reset_to_the_left( vec, index );
	}
	else
		shift_right( vec, index + 1 );
}

/*****************************************/

bool increment( const vector<reference_wrapper<Variable>> &variables )
{
	increment( variables, variables.size() - 1 );
}

void increment_some_vars( const vector<reference_wrapper<Variable>> &variables,
                          const vector<int> &vars_index )
{
	increment_some_vars( variables, vars_index, 0 );
}

void increment_boolean_vector( vector<bool> &vec )
{
	// increment_boolean_vector( vec, 0 );
	auto index = std::find_if( vec.begin(), vec.end(), []( auto b ){ return b; } );

	// if full of Trues
	if( std::all_of( vec.begin(), vec.end(), []( auto b ){ return b; } ) )
		return;

	// if full of Falses, start with True at vec[0]
	if( index == vec.end() )
	{
		*vec.begin() = true;
		return;
	}

	// if we cannot shift to the right a True, add a new True and reset everything to the left
	if( std::all_of( index, vec.end(), []( auto b ){ return b; } ) )
	{
		int number_trues = std::count_if( vec.begin(), vec.end(), []( auto b ){ return b; } );
		std::fill( vec.begin(), vec.end(), false );
		std::fill( vec.begin(), vec.begin() + number_trues + 1, true );
		return;
	}
	
	shift_right( vec, index );
}
