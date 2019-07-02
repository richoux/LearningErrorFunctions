#include "increment.hpp"

void increment( const vector<reference_wrapper<Variable>> &variables,
                const int limit )
{
	increment( variables, limit, variables.size() - 1 );
}

void increment( const vector<reference_wrapper<Variable>> &variables,
                const int limit,
                const int index )
{
	if( index < 0 )
		return;
	
	if( variables[ index ].get().get_value() < limit - 1 )
		variables[ index ].get().set_value( variables[ index ].get().get_value() + 1 );
	else
	{
		variables[ index ].get().set_value( 0 );
		increment( variables, limit, index - 1 );
	}
}

void increment_some_vars( const vector<reference_wrapper<Variable>> &variables,
                          const int limit,
                          const vector<int> &vars_index )
{
	increment_some_vars( variables, limit, vars_index, 0 );
}

void increment_some_vars( const vector<reference_wrapper<Variable>> &variables,
                          const int limit,
                          const vector<int> &vars_index,
                          const int index )
{
	if( index >= vars_index.size() )
		return;

	int current_var_index = vars_index[ index ];
	
	if( variables[ current_var_index ].get().get_value() < limit - 1 )
		variables[ current_var_index ].get().set_value( variables[ current_var_index ].get().get_value() + 1 );
	else
	{
		variables[ current_var_index ].get().set_value( 0 );
		increment_some_vars( variables, limit, vars_index, index + 1 );
	}
}
