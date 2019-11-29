#include <cmath>
#include <algorithm>

#include "all-diff.hpp"
#include "../learn/function_to_learn_cppn.hpp" // for number_functions
#include "../utils/convert.hpp"

// defined in cfn/function_to_learn_cppn.cpp
double intermediate_g( const vector<int>& weights,
                       const vector<double>& inputs,
                       int nb_vars,
                       int nb_params = 1,
                       double parameter_1 = 1,
                       double parameter_2 = 0 );

//////////////////////////////////////////////////////

// CPPN Max ECL+inactive - Ctr HO 96.6429
// _weights{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0 },

// CPPN Max ECL+inactive - Ctr HO 97.7071
// _weights{ 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },

// CPPN Max ECL+inactive - Ctr HO from feature/new_functions 52.7071
// _weights{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }

// CPPN Max ECL+inactive - Ctr HO on AllDiff_5 38.5786
// _weights{ 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }

// CPPN Max ECL+inactive - Ctr HO on AllDiff_5 new cost norm 34.7714
// _weights{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 }

// CPPN Max ECL+inactive - Ctr HO on AllDiff_9 new cost norm 43.3857
// _weights{ 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0 }

// Transo+Compar AllDiff
// raw_weights{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 }

// GA cost 12
// _weights{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _weights{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;

	auto weights = make_weights( _weights );
	//auto weights = _weights;
	
	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v.get().get_value(); } );

	return intermediate_g( weights, inputs, _ad_concept.nb_vars );
}

