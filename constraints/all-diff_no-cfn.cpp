#include <cmath>
#include <algorithm>

#include "all-diff_no-cfn.hpp"

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;
	else
		return 1.;
}

