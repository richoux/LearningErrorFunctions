#include <random>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "obj_ecl.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

#if defined DEBUG
static bool first = true;
#endif

Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector< vector<int> >& random_solutions )
	: Objective( "Max ECL" ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value ),
	  _random_sol( random_solutions ),
	  _index( vector<int>(_random_sol.size() ) )
{
	std::iota( _index.begin(), _index.end(), 0 );
}

double Obj_ECL::required_cost( const vector< Variable >& variables ) const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif
	
	vector<double> f_outputs;

	// prepare the random walk: we will visit solutions in random_solutions in a random order.
	_rng.shuffle( _index );
	
	// random starting point, since computing the empirical_autocorrelation assumes 
	// the space to be isotropic, ie, the starting point should not have any influence
	// on the statistical information obtained from the random walk.
	vector<int> current( _nb_vars );
	_rng.generate( current, 0, _max_value );

#if defined DEBUG
	if( first )
	{
		for( auto&c : current )
			cerr << c << " ";
		cerr << "Sol\n";
	}
#endif
	
	for( int i = 0; i < (int)_index.size(); )
	{
		auto output = std::abs( g( variables, current, _max_value ) );
		f_outputs.push_back( concept( current ) ? 0 : output );
		
	skip_compute_g:
		auto diff = std::mismatch( current.begin(), current.end(), _random_sol[ _index[i] ].begin() );
		if( diff.first == current.end() )
		{
			++i;
#if defined DEBUG
			if( first )
			{
				for( auto&c : current )
					cerr << c << " ";
				cerr << "Sol\n";
			}
#endif
			if( i == (int)_index.size() )
				break;
			else
				goto skip_compute_g;
		}
		else
		{
			*(diff.first) = *(diff.second);
#if defined DEBUG
			if( first )
			{
				for( auto&c : current )
					cerr << c << " ";
				cerr << "\n";
			}
#endif
		}
	}

#if defined DEBUG
	first = false;
#endif
	
	int length = (int)f_outputs.size();
	
	double mean;
	double sum = 0.;
	for( int i = 0; i < length; ++i )
		sum += f_outputs[ i ];
	mean = sum / length;
	
	double sum_diff_mean = 0.;
	double sum_diff_square = 0.;
	for( int i = 0; i < length - 1; ++i )
	{
		sum_diff_mean += ( ( f_outputs[ i ] - mean ) * ( f_outputs[ i + 1 ] - mean ) );
		sum_diff_square += std::pow( ( f_outputs[ i ] - mean ), 2 );
	}

	sum_diff_square += std::pow( ( f_outputs[ length - 1 ] - mean ), 2 );
	
	double empirical_autocorrelation_num = sum_diff_mean / ( length - 1 );
	double empirical_autocorrelation_den = sum_diff_square / length;
	double empirical_autocorrelation = empirical_autocorrelation_num / empirical_autocorrelation_den;

#if defined CHRONO
	auto end = std::chrono::steady_clock::now();
	cerr << "Obj_ECL::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
#endif
	
	return 1. / std::log( std::abs( empirical_autocorrelation ) );
}
