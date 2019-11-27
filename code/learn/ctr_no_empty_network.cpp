#include <algorithm>

#include "ctr_no_empty_network.hpp"

Ctr_no_empty_network::Ctr_no_empty_network( const vector< reference_wrapper<Variable> >& weights )
	: Constraint ( weights )
{ }

double Ctr_no_empty_network::required_cost() const
{
	if( std::count_if( variables.begin(), variables.end(), [](auto v){ return v.get().get_value() == 1; } ) == 0 )
		return 1;
	else
		return 0;
}

