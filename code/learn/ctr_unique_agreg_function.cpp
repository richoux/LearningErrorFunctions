#include <algorithm>

#include "ctr_unique_agreg_function.hpp"

Ctr_unique_agreg_function::Ctr_unique_agreg_function( const vector< reference_wrapper<Variable> >& weights )
	: Constraint ( weights )
{ }

double Ctr_unique_agreg_function::required_cost() const
{
	if( std::count_if( variables.begin(), variables.end(), [](auto v){ return v.get().get_value() == 1; } ) == 1 )
		return 0;
	else
		return 1;
}

