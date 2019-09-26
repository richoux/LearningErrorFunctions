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
#include "function_to_learn_trigo.hpp"
#include "concept.hpp"

#if defined CHRONO or DEBUG
static bool first = true;
#endif

//Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, vector< vector<int> > random_configurations, map<string, double> cost_map )
Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, const vector<int>& random_configurations, const map<string, double>& cost_map )
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

#if defined CHRONO
	if( first )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "Ctr_HO::assignement: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
	}
#endif

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

	double precomputed_metric;
	
	//for( const auto& c : _random_configurations )
	for( int i = 0; i < (int)_random_configurations.size(); i += _nb_vars )
	{
		//g_x = g( coefficients, c, _var_max_value );
		g_x = g( coefficients, _random_configurations, i, i + _nb_vars, _var_max_value );
		{
			//precomputed_metric = _cost_map.at( convert( c ) );
			precomputed_metric = _cost_map.at( convert( _random_configurations, i, i + _nb_vars ) );
			if( g_x < precomputed_metric )
				cost += ( precomputed_metric - g_x );
		}
	
#if defined DEBUG
		if( first )
		{
			cerr << "Configuration: ";
				for( int j = i; j < i + _nb_vars; ++j )
					cerr << _random_configurations[j] << " ";
			
			cerr << "\nPrecomputed metric: " << precomputed_metric
			     << ", local cost: " << g_x
			     << ", global cost: " << cost << "\n";
		}
#endif
	}

#if defined DEBUG
	if( first )
	{
		first = false;
	}
#endif
	
#if defined CHRONO
	if( first )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "Ctr_HO::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first = false;
	}
#endif
	return cost;
}

