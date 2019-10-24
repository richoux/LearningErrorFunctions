#include "ctr_inactive_unit.hpp"

Ctr_inactive_unit::Ctr_inactive_unit( const vector< reference_wrapper<Variable> >& weights )
	: Constraint ( weights )
{ }

// k+2 variables: the first k variables correspond to the id node from the k first layer
// the 2 remaining variables correspond to the id and abs node to the k+1 layer
// (which is the last one, without counting the added, final layer)
double Ctr_inactive_unit::required_cost() const
{
	bool inactive_unit = true;

	for( auto w : variables )
		if( w.get().get_value() == 1 )
		{
			inactive_unit = false;
			break;
		}

	if(	inactive_unit )
		return 0.0;
	else
		return 1.0;
}

