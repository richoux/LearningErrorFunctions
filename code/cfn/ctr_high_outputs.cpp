#include <algorithm>
#include <valarray>
#include <numeric>
#include <map>
#include <string>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "ctr_high_outputs.hpp"
#include "../latin/latin.hpp"
#include "../utils/convert.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, vector< vector<int> > random_configurations, map<string, double> cost_map )
	: Constraint (coefficients),
	  _nb_vars (nb_vars),
	  _var_max_value (var_max_value),
	  _random_configurations (random_configurations),
	  _cost_map (cost_map)
{ }

double Ctr_HO::required_cost() const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif

	// Do not get confused between variables of our model (the coefficients) and variables of the configuration search space
	auto& coefficients = variables;

	//LHS super slow!!
	// auto samples = _latin.sample( _nb_vars, _var_max_value );
	// vector< vector<int> > samples( _var_max_value );
	// for( int i = 0; i < _nb_vars; ++i )
	// {
	// 	samples[i] = vector<int>( _nb_vars );
	// 	_rng.generate( samples[i], 0, _var_max_value );
	// }

	double g_x;
	double cost = 0.;
	
	for( const auto& c : _random_configurations )
	{
		g_x = g( coefficients, c, _var_max_value );
		{
			double precomputed_metric = _cost_map.at( convert( c ) );
			if( g_x < precomputed_metric )
				cost += ( precomputed_metric - g_x );
		}
	}
	
#if defined CHRONO
	auto end = std::chrono::steady_clock::now();
	cerr << "Ctr_HO::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
#endif
	return cost;
}

