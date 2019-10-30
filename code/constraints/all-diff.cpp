#include <cmath>
#include <algorithm>

#include "all-diff.hpp"
#include "../learn/function_to_learn_cppn.hpp" // for number_functions

// defined in cfn/function_to_learn_cppn.cpp
double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int max );

//////////////////////////////////////////////////////

// CPPN Max ECL+inactive - Ctr HO 96.6429
// _weights{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 },

// CPPN Max ECL+inactive - Ctr HO 97.7071
// _weights{ 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },

// CPPN Max ECL+inactive - Ctr HO from feature/new_functions 52.7071
// _weights{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _weights{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v.get().get_value(); } );

	return intermediate_g( _weights, inputs, _ad_concept.nb_vars, _ad_concept.max_value );
}
