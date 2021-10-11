#include <cmath>
#include <algorithm>

#include "all-diff.hpp"
#include "../learn/function_to_learn_icn.hpp" // for number_functions
#include "../utils/convert.hpp"

// defined in cfn/function_to_learn_icn.cpp
double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& max_domain_value,
                       const int& nb_vars );

AllDiff::AllDiff( const vector<int>& index )
	: Constraint( index ),
	  _weights{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	  _ad_concept_{ (int)index.size(), (int)index.size() - 1 }
{ }

double AllDiff::required_error( const vector<Variable*>& variables ) const
{
	if( _ad_concept_.concept_( variables ) )
		return 0.;

	//auto weights = make_weights( _weights );
	auto weights = _weights;
	
	vector<double> inputs( variables.size() );
	std::transform( variables.begin(),
	                variables.end(),
	                inputs.begin(),
	                []( const auto& v ){ return v->get_value(); } );

	vector<double> param{ 1 };
	int nb_vars = _ad_concept_.nb_vars;
	int max_domain_value = _ad_concept_.max_value;
	
	return intermediate_g( inputs, param, weights, max_domain_value, nb_vars );
}

