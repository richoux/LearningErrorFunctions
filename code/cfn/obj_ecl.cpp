#include <random>
#include <cmath>
#include <algorithm>

#include <iterator>

#if defined CHRONO
#include <chrono>
#endif

#include "obj_ecl.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

#if defined DEBUG or CHRONO
static bool first2 = true;
#endif

//Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector< vector<int> >& random_solutions )
//Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector<int>& random_solutions )
Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector<int>& samples )
	: Objective( "Max ECL" ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value ),
	  _samples( samples )
	  //_random_sol( random_solutions ),
	  //_index( vector<int>( _random_sol.size() / nb_vars ) )
{
	//std::iota( _index.begin(), _index.end(), 0 );
}

double Obj_ECL::required_cost( const vector< Variable >& variables ) const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif
	
	vector<double> f_outputs;

	// prepare the random walk: we will visit solutions in random_solutions in a random order.
	//_rng.shuffle( _index );
	
	// random starting point, since computing the empirical_autocorrelation assumes 
	// the space to be isotropic, ie, the starting point should not have any influence
	// on the statistical information obtained from the random walk.
	vector<int> current( _nb_vars );
	double output;
	int backup;
	int length;
	
	double mean;
	double sum;
	double sum_diff_mean;
	double sum_diff_square;
	double empirical_autocorrelation_num;
	double empirical_autocorrelation_den;
	double empirical_autocorrelation;
	double total = 0.;

#if defined DEBUG
	if( first2 )
	{
		for( int i = 0; i < (int)_random_sol.size(); ++i )
		{
			if( i != 0 && i % _nb_vars == 0 )
				cerr << "\n";
			cerr << _random_sol[i] << " ";
		}
		cerr << "\n/////////////\n";
		
		for( auto&c : current )
			cerr << c << " ";
		cerr << "\n";
	}
#endif
	
	for( int i = 0; i < (int)_samples.size(); i+=_nb_vars )
	{
		f_outputs.clear();
		std::copy( _samples.begin() + i, _samples.begin() + i + _nb_vars, current.begin() );
		
		for( int v = 0; v < _nb_vars; ++v )
		{
			backup = current[v];
			for( int val = 0; val < _max_value; ++val )
			{
				current[v] = val;
				output = std::abs( g( variables, current, _max_value ) );
				f_outputs.push_back( concept( current ) ? 0 : output );
			}
			current[v] = backup;			
		}

// 	for( int i = 0; i < (int)_index.size(); )
// 	{
// 		auto output = std::abs( g( variables, current, _max_value ) );
// 		f_outputs.push_back( concept( current ) ? 0 : output );
		
// 	skip_compute_g:
// 		//auto diff = std::mismatch( current.begin(), current.end(), _random_sol[ _index[i] ].begin() );
// 		auto diff = std::mismatch( current.begin(), current.end(), _random_sol.begin() + _index[i] * _nb_vars, _random_sol.begin() + ( _index[i] + 1 ) * _nb_vars );
// 		if( diff.first == current.end() )
// 		{
// 			++i;
// #if defined DEBUG
// 			if( first2 )
// 			{
// 				for( auto&c : current )
// 					cerr << c << " ";
// 				cerr << "Sol\nTarget: ";
// 				for( int j = _index[i] * _nb_vars; j < ( _index[i] + 1 ) * _nb_vars; ++j )
// 					cerr << _random_sol[j] << " ";
// 				cerr << "\n";
// 			}
// #endif
// 			if( i == (int)_index.size() )
// 				break;
// 			else
// 				goto skip_compute_g;
// 		}
// 		else
// 		{
// 			*(diff.first) = *(diff.second);
// #if defined DEBUG
// 			if( first2 )
// 			{
// 				cerr << "Distances: " << distance( current.begin(), diff.first ) << "\n";
				
// 				for( auto&c : current )
// 					cerr << c << " ";
// 				cerr << "\n";
// 			}
// #endif
// 		}
// 	}

// #if defined DEBUG
// 	first2 = false;
// #endif
	
		length = (int)f_outputs.size();
	
		sum = 0.;
		for( int i = 0; i < length; ++i )
			sum += f_outputs[ i ];
		mean = sum / length;
		
		sum_diff_mean = 0.;
		sum_diff_square = 0.;
		for( int i = 0; i < length - 1; ++i )
		{
			sum_diff_mean += ( ( f_outputs[ i ] - mean ) * ( f_outputs[ i + 1 ] - mean ) );
			sum_diff_square += std::pow( ( f_outputs[ i ] - mean ), 2 );
		}
		
		sum_diff_square += std::pow( ( f_outputs[ length - 1 ] - mean ), 2 );
		
		empirical_autocorrelation_num = sum_diff_mean / ( length - 1 );
		empirical_autocorrelation_den = sum_diff_square / length;
		empirical_autocorrelation = empirical_autocorrelation_num / empirical_autocorrelation_den;
		total += ( 1. / std::log( std::abs( empirical_autocorrelation ) ) );
	}
	
#if defined CHRONO
	if( first2 )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "Obj_ECL::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first2 = false;
	}
#endif
	
	//return 1. / std::log( std::abs( empirical_autocorrelation ) );
	return total / ( (int)_samples.size() / _nb_vars );
}
