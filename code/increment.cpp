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
	
	if( variables[ index ].get_value() < limit )
		variables[ index ].set_value( variables[ index ].get_value() + 1 );
	else
	{
		variables[ index ].set_value( 0 );
		increment( variables, limit, index - 1);
	}
}
