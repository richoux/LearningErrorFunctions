#include <cmath>
#include <algorithm>

#include "all-diff.hpp"

// defined in cfn/function_to_learn_cppn.cpp
void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& result );

//////////////////////////////////////////////////////

//  CPPN  Max ECL+inactive - Ctr HO 97.7071
// 	weights{ 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 }

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _weights{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

// Learned CPPN cost function with CFN for all-diff 9
double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;

	int LO = ( _weights.size() / 7 ) * 10 + 1;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(), variables.end(), inputs.begin(), []( const auto& v ){ return v.get().get_value(); } );

	vector<double> result( _ad_concept.nb_vars );
	compute( LO, inputs, _weights, result );
	int number_units_last_layer = std::count( _weights.begin() + 7, _weights.begin() + 14, 1 );
	
	// cout << "nb var: " << _ad_concept.nb_vars
	//      << ", max val: " << _ad_concept.max_domain
	//      << ", max cost: " << _ad_concept.max_cost
	//      << "\n";
	
	// cout << "nb last units: " << number_units_last_layer << "\n";
	
	// std::copy( result.begin(), result.end(), std::ostream_iterator<double>( std::cout, ", " ) );
	// cout << "\n";

	// cout << "cost: " << _ad_concept.max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( _ad_concept.nb_vars * number_units_last_layer ) ) << "\n";
	
	return _ad_concept.max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( _ad_concept.nb_vars * number_units_last_layer ) );
}

// CPPN  Max ECL+inactive - Ctr HO 96.6429
// 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0

// CPPN  Max ECL+inactive - Ctr HO 97.7071
//0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0
