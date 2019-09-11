#include <algorithm>
#include <valarray>
#include <numeric>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "ctr_high_outputs.hpp"
#include "../latin/latin.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

Ctr_HO::Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value )
	: Constraint (coefficients),
	  _nb_vars (nb_vars),
	  _var_max_value (var_max_value)
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
	vector< vector<int> > samples( _var_max_value );
	for( int i = 0; i < _nb_vars; ++i )
	{
		samples[i] = vector<int>( _nb_vars );
		_rng.generate( samples[i], 0, _var_max_value );
	}
	
	double g_x;
	double counter = 0.;
	
	for( const auto& s : samples )
	{
		g_x = g( coefficients, s, _var_max_value );
		if( !concept( s ) && g_x < 1 )
			counter += ( 1 - g_x );
	}
	
#if defined CHRONO
	auto end = std::chrono::steady_clock::now();
	cerr << "Ctr_HO::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
#endif
	return counter;
}

