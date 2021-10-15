#include <cmath>
#include <algorithm>

#include "linear-leq_no-cfn.hpp"


LinearLeq::LinearLeq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _rhs( rhs ),
	  _le_concept_{ (int)variables.size(), max_value, rhs }
{ }

double LinearLeq::required_error( const vector<Variable*>& variables ) const
{
	if( _le_concept_.concept_( variables ) )
		return 0.;
	else
		return 1.;
}
