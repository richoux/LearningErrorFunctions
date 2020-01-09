#include <cmath>
#include <algorithm>

#include "all-diff_hardcoded.hpp"

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;

	int cost = 0;

	for( int i = 0 ; i < (int)variables.size() - 1 ; ++i )
	{
		auto number_equals_on_the_right = std::count_if( variables.begin() + i + 1,
		                                                 variables.end(),
		                                                 [&]( auto v ){ return v.get().get_value() == variables[i].get().get_value(); } );
		if( number_equals_on_the_right > 0 )
			++cost;
	}

	return cost;
}

