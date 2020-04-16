#include <algorithm>

#include "linear-eq.hpp"
#include "../learn/function_to_learn_icn.hpp" // for number_functions

// defined in cfn/function_to_learn_icn.cpp
double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& max_domain_value,
                       const int& nb_vars );

LinearEq::LinearEq( const vector< reference_wrapper<Variable> >& variables, int max_value, int rhs )
	: Constraint( variables ),
	  _weights{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
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

	vector<double> param{ static_cast<double>( _rhs ) };

	return intermediate_g( inputs, param, _weights, _le_concept.max_value, _le_concept.nb_vars );
}
