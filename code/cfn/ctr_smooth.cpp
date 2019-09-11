#include <algorithm>
#include <valarray>
#include <numeric>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "ctr_smooth.hpp"
#include "../latin/latin.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

Ctr_smooth::Ctr_smooth( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value )
	: Constraint (coefficients),
	  _nb_vars (nb_vars),
	  _var_max_value (var_max_value)
{ }

double Ctr_smooth::required_cost() const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif

	// Do not get confused between variables of our model (the coefficients) and variables of the configuration search space
	auto& coefficients = variables;

	//LHS super slow!!
	// auto samples = _latin.sample( _nb_vars, _var_max_value );
	vector< vector<int> > samples( _nb_vars );
	for( int i = 0; i < _nb_vars; ++i )
		_rng.generate( samples[i], 0, _var_max_value );
	
	double g_x, mean, diff, std_dev;

	// iterations = 25% of the neighborhood size
	int iter = ( ( _var_max_value - 1 ) * _nb_vars ) / 4; 
	
	vector<double> g_outputs( iter );
	int index, value;

	double max_diff = 0.;
	
	for( const auto& s : samples )
	{
		if( !concept( s ) )
		{
			g_x = g( coefficients, s, _var_max_value );

			for( int i = 0; i < iter; ++i )
			{
				auto neighbor = s;
				
				do
				{
					index = _rng.uniform( 0, _nb_vars - 1 );
					value = _rng.uniform( 0, _var_max_value );
				}
				while( neighbor[ index ] == value );
				neighbor[ index ] = value;

				g_outputs[i] = g( coefficients, neighbor, _var_max_value );
			}

			mean = std::accumulate( g_outputs.begin(), g_outputs.end(), 0. ) / iter;

			// sample standard deviation (justifying the division by 'iter-1')
			std_dev = std::sqrt( std::accumulate( g_outputs.begin(),
			                                      g_outputs.end(),
			                                      0.,
			                                      [&]( double total, auto g ){ return total + std::pow( ( g - mean ), 2 ); })
			                     / ( iter - 1 ) );

			diff = std::abs( g_x - mean );
			if( diff > std_dev && diff > max_diff )
				max_diff = diff;
		}
	}
	
#if defined CHRONO
	auto end = std::chrono::steady_clock::now();
	cerr << "Ctr_smooth::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
#endif
	return max_diff;
}

