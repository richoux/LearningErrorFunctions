#include <algorithm>
#include <valarray>
#include <numeric>
#include <map>
#include <string>
#include <cmath>

#include "ctr_high_outputs.hpp"
#include "../latin/latin.hpp"
#include "../utils/convert.hpp"
#include "function_to_learn_cppn.hpp"

//Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, vector< vector<int> > random_configurations, map<string, double> cost_map )
Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& weight_vars, int nb_vars, const vector<int>& random_configurations, const map<string, double>& cost_map )
	: Constraint( weight_vars ),
	  _nb_vars( nb_vars ),
	  _random_configurations( random_configurations ),
	  _cost_map( cost_map )
{
	_weights.reserve( weight_vars.size() + number_functions );
	_inputs.reserve( nb_vars );
}

double Ctr_HO::required_cost() const
{
	// Do not get confused between variables of our model (the coefficients) and variables of the configuration search space
	auto& weight_vars = variables;

	double g_x;
	double cost = 0.;
	double precomputed_metric;

	_weights.resize( _weights.capacity() );
	std::transform( weight_vars.begin(), weight_vars.end(), _weights.begin(), [&]( auto w ){ return w.get().get_value(); } );

	// Last layer: identity
	std::fill( _weights.begin() + weight_vars.size(), _weights.end(), 0 );
	_weights[ weight_vars.size() ] = 1;

	for( int i = 0; i < (int)_random_configurations.size(); i += _nb_vars )
	{
		_inputs.resize( _inputs.capacity() );
		std::copy( _random_configurations.begin() + i, _random_configurations.begin() + i + _nb_vars, _inputs.begin() );

		g_x = g( _weights, _inputs, i, i + _nb_vars );
		precomputed_metric = _cost_map.at( convert( _random_configurations, i, i + _nb_vars ) );
		if( g_x < precomputed_metric )
			cost += ( precomputed_metric - g_x );
	}

	return cost;
}

