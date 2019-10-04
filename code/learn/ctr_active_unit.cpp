#include "ctr_active_unit.hpp"

Ctr_active_unit::Ctr_active_unit( const vector< reference_wrapper<Variable> >& weights )
	: Constraint (weights)
{ }

double Ctr_active_unit::required_cost() const
{
	bool active_unit = false;

	for( auto w : variables )
		if( w.get().get_value() == 1 )
		{
			active_unit = true;
			break;
		}

	if(	active_unit )
		return 0.0;
	else
		return 1.0;
}

