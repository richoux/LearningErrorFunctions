#include <algorithm>
#include <cmath>

#include "concept.hpp"

bool Concept::concept() const
{
	vector<int> vars( _nb_vars );
	std::transform( variables.begin(), variables.end(), vars.begin(), []( const auto& v ){ return v.get().get_value(); } );
	
	return concept( vars );
}

Concept::Concept( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables),
	  nb_vars( (int)variables.size() ),
	  max_domain( nb_vars - 1),
	  max_cost( nb_vars + ( max_domain / ( std::pow( 10, std::floor( std::log10( max_domain ) ) + 1 ) ) ) )
{ }

double Concept::required_cost() const
{
	if( concept() )
		return 0.;

	weights.insert( weights.end(), {0,1,0,0,0,0,0} );
	
	int LO = ( weights.size() / 7 ) * 10 + 1;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(), variables.end(), inputs.begin(), [&]( auto v ){ return v.get().get_value(); } );

	vector<double> result( nb_vars );
	compute( LO, inputs, weights, result );
	int number_units_last_layer = std::count( weights.begin() + 7, weights.begin() + 14, 1 );
		
	return max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) );
}
