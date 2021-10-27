#include <algorithm>

#include "linear-eq.hpp"
#include "../learn_ga/function_to_learn_icn.hpp" // for number_functions

// defined in cfn/function_to_learn_icn.cpp
double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& max_domain_value,
                       const int& nb_vars );

LinearEq::LinearEq( const vector<int>& variables, int max_value, int rhs )
	: Constraint( variables ),
	  // Hamming
    // _weights{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	  // Manhattan
	  _weights{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	  _rhs( rhs ),
	  _le_concept_{ (int)variables.size(), max_value, rhs }
{ }

double LinearEq::required_error( const vector<Variable*>& variables ) const
{
	if( _le_concept_.concept_( variables ) )
		return 0.;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v->get_value(); } );

	vector<double> param{ static_cast<double>( _rhs ) };

	return intermediate_g( inputs, param, _weights, _le_concept_.max_value, _le_concept_.nb_vars );
}
