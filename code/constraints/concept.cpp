#include <cmath>

#include "concept.hpp"

Concept::Concept( int nb_vars, int max_value )
	: nb_vars( nb_vars ),
	  max_value( max_value ),
	  max_cost( nb_vars + ( max_value / ( std::pow( 10, std::floor( std::log10( max_value ) ) + 1 ) ) ) )
{ }

bool Concept::concept( const vector<int>& var ) const
{
	return concept( var, 0, (int)var.size() );
}
