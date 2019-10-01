#include <random>
#include <cmath>
#include <algorithm>

#include <iterator>

#if defined CHRONO
#include <chrono>
#endif

#include "obj_ecl.hpp"
#include "function_to_learn_cppn.hpp"
//#include "function_to_learn_trigo.hpp"
#include "concept.hpp"

#if defined DEBUG or CHRONO
static bool first2 = true;
#endif

//Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector< vector<int> >& random_solutions )
//Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector<int>& random_solutions )
Obj_ECL::Obj_ECL( int nb_vars, int max_value, const vector<int>& random_solutions, const vector<int>& samples )
	: Objective( "Max empirical autocorrelation function" ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value ),
	  _random_sol( random_solutions ),
	  _random_config( samples )
{
	_walk.resize( 2 * _random_sol.size() );
	for( int i = 0; i < (int)_random_sol.size(); i+=_nb_vars )
	{
		std::copy( _random_config.begin() + i, _random_config.begin() + i + _nb_vars, _walk.begin() + i );
		std::copy( _random_sol.begin() + i, _random_sol.begin() + i + _nb_vars, _walk.begin() + i + _nb_vars );		
	}
}

double Obj_ECL::required_cost( const vector< Variable >& variables ) const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif
	
	vector<double> f_outputs;

	// prepare the random _walk: we will visit solutions in random_solutions in a random order.
	//_rng.shuffle( _index );
	
	// random starting point, since computing the empirical_autocorrelation assumes 
	// the space to be isotropic, ie, the starting point should not have any influence
	// on the statistical information obtained from the random _walk.
	
	vector<int> current( _nb_vars );
	int length;
	
	double mean;
	double sum;
	double sum_diff_mean;
	double sum_diff_square;
	double empirical_autocorrelation_num;
	double empirical_autocorrelation_den;
	double empirical_autocorrelation;

	for( int i = 0; i < 2*(int)_random_sol.size() - _nb_vars; i += _nb_vars )
	{
		std::copy( _walk.begin() + i, _walk.begin() + i + _nb_vars, current.begin() );

		auto diff = std::mismatch( current.begin(),
		                           current.end(),
		                           _walk.begin() + i + _nb_vars,
		                           _walk.begin() + i + 2 * _nb_vars );
		// cout << "Target: ";
		// for( int j = 0; j < _nb_vars; ++j )
		// 	cout << _walk[i + _nb_vars +j ] << " ";
		// cout << "\n";

		while( diff.first != current.end() )
		{
			// cout << "Current: ";
			// for( auto c : current )
			// 	cout << c << " ";
			// cout << "\n";

			auto output = g( variables, current, _max_value );

			// cout << "current cost: " << output << "\n";
			
			f_outputs.push_back( concept( current ) ? 0 : output );
			*(diff.first) = *(diff.second);

			diff = std::mismatch( current.begin(),
			                      current.end(),
			                      _walk.begin() + i + _nb_vars,
			                      _walk.begin() + i + 2 * _nb_vars );
		}

		// cout << "Current (= Target?): ";
		// for( auto c : current )
		// 	cout << c << " ";
		// cout << "\n";
		
		auto output = g( variables, current, _max_value );
		f_outputs.push_back( concept( current ) ? 0 : output );
		// cout << "target cost: " << output << "\n";
	}
	
	length = (int)f_outputs.size();
	
	sum = 0.;
	for( int j = 0; j < length; ++j )
	{
		sum += f_outputs[ j ];
		//cerr << "f_outputs[" << j << "]=" << f_outputs[ j ] << "\n";
	}
	mean = sum / length;
		
	sum_diff_mean = 0.;
	sum_diff_square = 0.;
	for( int j = 0; j < length - 1; ++j )
	{
		sum_diff_mean += ( ( f_outputs[ j ] - mean ) * ( f_outputs[ j + 1 ] - mean ) );
		sum_diff_square += std::pow( ( f_outputs[ j ] - mean ), 2 );
	}
	
	sum_diff_square += std::pow( ( f_outputs[ length - 1 ] - mean ), 2 );
	
	empirical_autocorrelation_num = sum_diff_mean / ( length - 1 );
	empirical_autocorrelation_den = sum_diff_square / length;
		
	empirical_autocorrelation = empirical_autocorrelation_num / empirical_autocorrelation_den;
	//total += ( 1. / std::log( std::abs( empirical_autocorrelation ) ) );
	//total += empirical_autocorrelation;
	
#if defined CHRONO
	if( first2 )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "Obj_ECL::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first2 = false;
	}
#endif

	return - empirical_autocorrelation;
	
	//return 1. / std::log( std::abs( empirical_autocorrelation ) );
	//return std::abs( total / ( (int)_random_sol.size() / _nb_vars ) );
}
