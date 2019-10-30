#include <algorithm>

#include "linear-eq.hpp"
#include "../learn/function_to_learn_cppn.hpp" // for number_functions

// defined in cfn/function_to_learn_cppn.cpp
double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int max );

//////////////////////////////////////////////////////

// !!! AllDiff weights !!!

// CPPN Max ECL+inactive - Ctr HO from feature/new_functions 52.7071
// _weights{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }

LinearEq::LinearEq( const vector< reference_wrapper<Variable> >& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _weights{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
	  _rhs( rhs ),
	  _le_concept{ (int)variables.size(), max_value, rhs }
{ }

double LinearEq::required_cost() const
{
	if( _le_concept.concept( variables ) )
		return 0.;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v.get().get_value(); } );

	return intermediate_g( _weights, inputs, _le_concept.nb_vars, _le_concept.max_value );
}

