#include <random>
#include <cmath>
#include <algorithm>

#include <iterator>

#include "obj_ecl.hpp"
#include "function_to_learn_cppn.hpp"

Obj_ECL::Obj_ECL( unique_ptr<Concept> concept, int nb_vars, const vector<int>& random_solutions, const vector<int>& samples )
	: Objective( "Max empirical autocorrelation function + Max inactive units" ),
	  _concept( std::move( concept ) ),
	  _nb_vars( nb_vars ),
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

		while( diff.first != current.end() )
		{
			auto output = g( variables, current, _concept->max_domain );

			f_outputs.push_back( _concept->concept( current ) ? 0 : output );
			*(diff.first) = *(diff.second);

			diff = std::mismatch( current.begin(),
			                      current.end(),
			                      _walk.begin() + i + _nb_vars,
			                      _walk.begin() + i + 2 * _nb_vars );
		}

		auto output = g( variables, current, _concept->max_domain );
		f_outputs.push_back( _concept->concept( current ) ? 0 : output );
	}
	
	length = (int)f_outputs.size();
	
	sum = 0.;

	for( int j = 0; j < length; ++j )
		sum += f_outputs[ j ];

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
	
	int EA = static_cast<int>( std::trunc( empirical_autocorrelation * 100 ) );
	double inactives = std::count_if( variables.begin(), variables.end(), [](const auto &v){ return v.get_value() == 0; } );
	// normalization
	inactives = 0.9 * ( inactives / variables.size() );

	return -( EA + inactives );
}
