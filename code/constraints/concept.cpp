#include <cmath>

#include "concept.hpp"

Concept::Concept( int nb_vars, int max_domain )
	: nb_vars( nb_vars ),
	  max_domain( max_domain ),
	  max_cost( nb_vars + ( max_domain / ( std::pow( 10, std::floor( std::log10( max_domain ) ) + 1 ) ) ) )
{ }

bool Concept::concept( const vector<int>& var ) const
{
	return concept( var, 0, (int)var.size() );
}
