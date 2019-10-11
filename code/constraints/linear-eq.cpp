#include <algorithm>

#include "linear-eq.hpp"

LinearEq::LinearEq( const vector< reference_wrapper<Variable> >& variables, int rv )
	: Concept( variables, { 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 } ), // all-diff weights
	  _right_value( rv )
{ }

bool LinearEq::concept( const vector<int>& var ) const
{
	return std::accumulate( var.begin(), var.end(), 0 ) == _right_value;
}



