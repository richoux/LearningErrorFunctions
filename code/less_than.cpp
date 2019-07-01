#include "less_than.hpp"

LessThan::LessThan( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables)
{ }

double LessThan::required_cost() const
{
	// return 0 (meaning we have a solution) iff x[0] < x[1] < ... < x[n]
	for( int i = 0 ; i < variables.size() - 1 ; ++i )
		if( variables[i].get_value() >= variables[i+1].get_value() )
			return 1;
	
	return 0;
}
