#include <random>
#include <cmath>

#include "obj_ecl.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

Obj_ECL::Obj_ECL( int length, int nb_vars, int max_value )
	: Objective( "Max ECL" ),
	  _length( length ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value )
{ }

double Obj_ECL::required_cost( const vector< Variable >& variables ) const
{
	vector<double> g_outputs( _length );
	vector<double> f_outputs( _length );

	vector<int> walk( _nb_vars );
	
	// random starting point
	for( int i = 0; i < _nb_vars; ++i )
		walk[i] = _rng.uniform( 0, _max_value );

	for( int i = 0; i < _length; ++i )
	{
		g_outputs[ i ] = std::abs( g( variables, walk, _max_value ) );
		f_outputs[ i ] = concept( walk ) ? 0 : g_outputs[ i ];
		
		// new point from a random walk (local move)
		int var_to_change = _rng.uniform( 0, _nb_vars - 1 );
		int value_to_change;
		while( ( value_to_change = _rng.uniform( 0, _max_value ) ) == walk[ var_to_change ] ) {} // get a new value
		walk[ var_to_change ] = value_to_change;
	}

	double mean;
	double sum = 0.;
	for( int i = 0; i < _length; ++i )
		sum += f_outputs[ i ];
	mean = sum / _length;
	
	double sum_diff_mean = 0.;
	double sum_diff_square = 0.;
	for( int i = 0; i < _length - 1; ++i )
	{
		sum_diff_mean += ( ( f_outputs[ i ] - mean ) * ( f_outputs[ i + 1 ] - mean ) );
		sum_diff_square += std::pow( ( f_outputs[ i ] - mean ), 2 );
	}

	sum_diff_square += std::pow( ( f_outputs[ _length - 1 ] - mean ), 2 );
	
	double empirical_autocorrelation_num = sum_diff_mean / ( _length - 1 );
	double empirical_autocorrelation_den = sum_diff_square / _length;
	double empirical_autocorrelation = empirical_autocorrelation_num / empirical_autocorrelation_den;
	return 1. / std::log( std::abs( empirical_autocorrelation ) );
}
