#include <cmath>
#include <algorithm>

#include "all-diff_no-cfn.hpp"

AllDiff::AllDiff( const vector< Variable >& variables )
	: Constraint( variables ),
	  _ad_concept_{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_error( const vector< Variable >& variables ) const
{
	if( _ad_concept_.concept_( variables ) )
		return 0.;
	else
		return 1.;
}

