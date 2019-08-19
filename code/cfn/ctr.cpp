#include <algorithm>

#include "ctr.hpp"
#include "latin.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"


Ctr::Ctr( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables)
{ }

double Ctr::required_cost() const
{
	auto samples = LHS( variables );
	
	double counter = 0;

	for( const auto& s : samples )
	{
		int max = *( std::max_element( begin(s), end(s) ) );
		double g_x = g( variables, s, max );
		if( !concept( s ) && g_x < 1 )
			counter += g_x;
	}		
	
	return counter;
}
