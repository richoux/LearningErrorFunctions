#include "ctr_dependency.hpp"

Ctr_dependency::Ctr_dependency( const vector< reference_wrapper<Variable> >& weights )
	: Constraint (weights)
{ }

double Ctr_dependency::required_cost() const
{
	bool dependency_check = false;
	
	if( variables[7].get().get_value() == 0 )
		dependency_check = true;
	
	if( variables[7].get().get_value() == 1 )
		for( int i = 0; i < 7; ++i )
			if( variables[i].get().get_value() == 1 )
			{
				dependency_check = true;
				break;
			}

	if(	dependency_check )
		return 0.0;
	else
		return 1.0;
}

