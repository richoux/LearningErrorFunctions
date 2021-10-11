#include <cmath>
#include <algorithm>

#include "all-diff_hardcoded.hpp"

AllDiff::AllDiff( const vector<int>& index )
	: Constraint( index ),
	  _ad_concept_{ (int)index.size(), (int)index.size() - 1 }
{ }

double AllDiff::required_error( const vector<Variable*>& variables ) const
{
	if( _ad_concept_.concept_( variables ) )
		return 0.;

	int cost = 0;

	for( int i = 0 ; i < (int)variables.size() - 1 ; ++i )
	{
		auto value = variables[i]->get_value();		
		auto number_equals_on_the_right = std::count_if( variables.cbegin() + i + 1,
		                                                 variables.cend(),
		                                                 [&]( const auto& v ){ return v->get_value() == value; } );
		if( number_equals_on_the_right > 0 )
			++cost;
	}

	return cost;
}

