#include <cmath>
#include <algorithm>

#include "all-diff.hpp"
#include "../learn/function_to_learn_cppn.hpp" // for number_functions
#include "../utils/convert.hpp"

// defined in cfn/function_to_learn_cppn.cpp
double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& nb_vars );

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

// GA 4-layers cost 517.214
// _weights{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint( variables ),
	  _weights{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
	  _ad_concept{ (int)variables.size(), (int)variables.size() - 1 }
{ }

double AllDiff::required_cost() const
{
	if( _ad_concept.concept( variables ) )
		return 0.;

	//auto weights = make_weights( _weights );
	auto weights = _weights;
	
	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v.get().get_value(); } );

	vector<double> param{ 1 };
	int nb_vars = _ad_concept.nb_vars;
	
	return intermediate_g( inputs, param, weights, nb_vars );
}

