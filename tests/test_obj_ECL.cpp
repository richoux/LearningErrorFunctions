#include <iostream>
#include <vector>
#include <cmath>

#include "../utils/randutils.hpp"

using namespace std;

constexpr int ITER = 300;

double smooth_function( const vector<int>& vec )
{
	double total = 0.;

	for( auto v : vec )
		total += v*v;

	return total;
}

double not_so_smooth_function( const vector<int>& vec )
{
	double total = 0.;

	for( auto v : vec )
		total += sin( 10 * v );

	return total;
}

double random_function( randutils::mt19937_rng& rng )
{
	return rng.variate<double, std::uniform_real_distribution>(0.0,10.0);
}


double compute_ECL( int size, double& smooth, double& not_so_smooth )
{
	randutils::mt19937_rng _rng;
	vector<double> smooth_outputs;
	vector<double> not_so_smooth_outputs;
	vector<double> random_outputs;
	
	vector<int> current( size );
	vector<int> next_point( size );
	_rng.generate( current, 0, size - 1 );

	for( int i = 0; i < ITER; ++i )
	{
		_rng.generate( next_point, 0, size - 1 );

		std::pair<vector<int>::iterator, vector<int>::iterator> diff;
		
		do
		{
			smooth_outputs.push_back( smooth_function( current ) );
			not_so_smooth_outputs.push_back( not_so_smooth_function( current ) );
			random_outputs.push_back( random_function( _rng ) );
			
			diff = std::mismatch( current.begin(),
			                      current.end(),
			                      next_point.begin() );
			
			*(diff.first) = *(diff.second);
		}
		while( diff.first != current.end() );

		smooth_outputs.push_back( smooth_function( current ) );
		not_so_smooth_outputs.push_back( not_so_smooth_function( current ) );
		random_outputs.push_back( random_function( _rng ) );
	}

	int length = (int)smooth_outputs.size();
	
	double mean_smooth;
	double mean_not_so_smooth;
	double mean_random;

	double sum_smooth = 0.;
	double sum_not_so_smooth = 0.;
	double sum_random = 0.;
	
	for( int i = 0; i < length; ++i )
	{
		sum_smooth += smooth_outputs[ i ];
		sum_not_so_smooth += not_so_smooth_outputs[ i ];
	}

	mean_smooth = sum_smooth / length;
	mean_not_so_smooth = sum_not_so_smooth / length;
	
	double sum_diff_mean_smooth = 0.;
	double sum_diff_mean_not_so_smooth = 0.;
	double sum_diff_mean_random = 0.;
	
	double sum_diff_square_smooth = 0.;
	double sum_diff_square_not_so_smooth = 0.;
	double sum_diff_square_random = 0.;

	for( int i = 0; i < length - 1; ++i )
	{
		sum_diff_mean_smooth += std::abs( ( smooth_outputs[ i ] - mean_smooth ) * ( smooth_outputs[ i + 1 ] - mean_smooth ) );
		sum_diff_mean_not_so_smooth += std::abs( ( not_so_smooth_outputs[ i ] - mean_not_so_smooth ) * ( not_so_smooth_outputs[ i + 1 ] - mean_not_so_smooth ) );
		sum_diff_mean_random += std::abs( ( random_outputs[ i ] - mean_random ) * ( random_outputs[ i + 1 ] - mean_random ) );

		sum_diff_square_smooth += std::pow( ( smooth_outputs[ i ] - mean_smooth ), 2 );
		sum_diff_square_not_so_smooth += std::pow( ( not_so_smooth_outputs[ i ] - mean_not_so_smooth ), 2 );
		sum_diff_square_random += std::pow( ( random_outputs[ i ] - mean_random ), 2 );
	}

	sum_diff_square_smooth += std::pow( ( smooth_outputs[ length - 1 ] - mean_smooth ), 2 );
	sum_diff_square_not_so_smooth += std::pow( ( not_so_smooth_outputs[ length - 1 ] - mean_not_so_smooth ), 2 );
	sum_diff_square_random += std::pow( ( random_outputs[ length - 1 ] - mean_random ), 2 );

	double empirical_autocorrelation_num_smooth = sum_diff_mean_smooth / ( length - 1 );
	double empirical_autocorrelation_den_smooth = sum_diff_square_smooth / length;
	double empirical_autocorrelation_smooth = empirical_autocorrelation_num_smooth / empirical_autocorrelation_den_smooth;

	double empirical_autocorrelation_num_not_so_smooth = sum_diff_mean_not_so_smooth / ( length - 1 );
	double empirical_autocorrelation_den_not_so_smooth = sum_diff_square_not_so_smooth / length;
	double empirical_autocorrelation_not_so_smooth = empirical_autocorrelation_num_not_so_smooth / empirical_autocorrelation_den_not_so_smooth;

	double empirical_autocorrelation_num_random = sum_diff_mean_random / ( length - 1 );
	double empirical_autocorrelation_den_random = sum_diff_square_random / length;
	double empirical_autocorrelation_random = empirical_autocorrelation_num_random / empirical_autocorrelation_den_random;

	smooth = std::abs( empirical_autocorrelation_smooth );
	not_so_smooth = std::abs( empirical_autocorrelation_not_so_smooth );
	return std::abs( empirical_autocorrelation_random );

	// smooth = 1. / std::log( std::abs( empirical_autocorrelation_smooth ) );
	// not_so_smooth = 1. / std::log( std::abs( empirical_autocorrelation_not_so_smooth ) );
}

double compute_local_correlation( int size, double& smooth, double& not_so_smooth )
{
	randutils::mt19937_rng _rng;
	vector<double> smooth_outputs;
	vector<double> not_so_smooth_outputs;
	vector<double> random_outputs;
	
	vector<int> current( size );
	int backup;

	double tmp_random = 0.;
	
	smooth = 0.;
	not_so_smooth = 0.;
	
	for( int i = 0; i < ITER; ++i )
	{
		_rng.generate( current, 0, size - 1 );

		for( int v = 0; v < size; ++v )
		{
			smooth_outputs.clear();
			not_so_smooth_outputs.clear();
			random_outputs.clear();

			backup = current[v];
			for( int val = 0; val < size; ++val )
			{
				current[v] = val;
				smooth_outputs.push_back( smooth_function( current ) );
				not_so_smooth_outputs.push_back( not_so_smooth_function( current ) );
				random_outputs.push_back( random_function( _rng ) );
			}
			current[v] = backup;			
		
			int length = size;
			//int length = (int)smooth_outputs.size();
			
			double mean_smooth;
			double mean_not_so_smooth;
			double mean_random;
			
			double sum_smooth = 0.;
			double sum_not_so_smooth = 0.;
			double sum_random = 0.;
			
			for( int j = 0; j < length; ++j )
			{
				sum_smooth += smooth_outputs[ j ];
				sum_not_so_smooth += not_so_smooth_outputs[ j ];
				sum_random += random_outputs[ j ];
			}
			
			mean_smooth = sum_smooth / length;
			mean_not_so_smooth = sum_not_so_smooth / length;
			mean_random = sum_random / length;
			
			double sum_diff_mean_smooth = 0.;
			double sum_diff_mean_not_so_smooth = 0.;
			double sum_diff_mean_random = 0.;
			
			double sum_diff_square_smooth = 0.;
			double sum_diff_square_not_so_smooth = 0.;
			double sum_diff_square_random = 0.;
			
			for( int j = 0; j < length - 1; ++j )
			{
				sum_diff_mean_smooth += ( ( smooth_outputs[ j ] - mean_smooth ) * ( smooth_outputs[ j + 1 ] - mean_smooth ) );
				sum_diff_mean_not_so_smooth += ( ( not_so_smooth_outputs[ j ] - mean_not_so_smooth ) * ( not_so_smooth_outputs[ j + 1 ] - mean_not_so_smooth ) );
				sum_diff_mean_random += ( ( random_outputs[ j ] - mean_random ) * ( random_outputs[ j + 1 ] - mean_random ) );
				
				sum_diff_square_smooth += std::pow( ( smooth_outputs[ j ] - mean_smooth ), 2 );
				sum_diff_square_not_so_smooth += std::pow( ( not_so_smooth_outputs[ j ] - mean_not_so_smooth ), 2 );
				sum_diff_square_random += std::pow( ( random_outputs[ j ] - mean_random ), 2 );
			}
			
			sum_diff_square_smooth += std::pow( ( smooth_outputs[ length - 1 ] - mean_smooth ), 2 );
			sum_diff_square_not_so_smooth += std::pow( ( not_so_smooth_outputs[ length - 1 ] - mean_not_so_smooth ), 2 );
			sum_diff_square_random += std::pow( ( random_outputs[ length - 1 ] - mean_random ), 2 );
			
			double empirical_autocorrelation_num_smooth = sum_diff_mean_smooth / ( length - 1 );
			double empirical_autocorrelation_den_smooth = sum_diff_square_smooth / length;
			double empirical_autocorrelation_smooth = empirical_autocorrelation_num_smooth / empirical_autocorrelation_den_smooth;
			
			double empirical_autocorrelation_num_not_so_smooth = sum_diff_mean_not_so_smooth / ( length - 1 );
			double empirical_autocorrelation_den_not_so_smooth = sum_diff_square_not_so_smooth / length;
			double empirical_autocorrelation_not_so_smooth = empirical_autocorrelation_num_not_so_smooth / empirical_autocorrelation_den_not_so_smooth;
			
			double empirical_autocorrelation_num_random = sum_diff_mean_random / ( length - 1 );
			double empirical_autocorrelation_den_random = sum_diff_square_random / length;
			double empirical_autocorrelation_random = empirical_autocorrelation_num_random / empirical_autocorrelation_den_random;
		
			tmp_random += std::abs( empirical_autocorrelation_random );
			
			smooth += std::abs( empirical_autocorrelation_smooth );	
			not_so_smooth += std::abs( empirical_autocorrelation_not_so_smooth );
			// tmp_smooth += ( 1. / std::log( std::abs( empirical_autocorrelation_smooth ) ) );
			// tmp_not_so_smooth += ( 1. / std::log( std::abs( empirical_autocorrelation_not_so_smooth ) ) );
			// tmp_random += ( 1. / std::log( std::abs( empirical_autocorrelation_random ) ) );
			
			// smooth += std::abs( tmp_smooth );	
			// not_so_smooth += std::abs( tmp_not_so_smooth );
		}
	}

	smooth = std::abs( smooth / ( ITER * size ) );
	not_so_smooth = std::abs( not_so_smooth / ( ITER * size ) );

	return std::abs( tmp_random / ( ITER * size ) );
	
	// smooth = tmp_smooth / ITER;
	// not_so_smooth = tmp_not_so_smooth / ITER;
}

void sample_local_minimum( int size, double& smooth, double& not_so_smooth )
{
	randutils::mt19937_rng _rng;
	vector<int> sample( size );
	double cost_smooth, cost_not_so_smooth;
	double cost_neighbor_smooth, cost_neighbor_not_so_smooth;

	int lm_smooth = 0;
	int lm_not_so_smooth = 0;

	int backup;
	
	for( int i = 0; i < 1000000; ++i )
	{
		_rng.generate( sample, 0, size - 1 );

		cost_smooth = smooth_function( sample );
		cost_not_so_smooth = not_so_smooth_function( sample );

		bool local_smooth = true;
		bool local_not_so_smooth = true;
		
		for( int v = 0; v < size && ( local_smooth || local_not_so_smooth ); ++v )
		{
			backup = sample[v];

			for( int val = 0; val < size && ( local_smooth || local_not_so_smooth ); ++val )
			{
				sample[v] = val;
				cost_neighbor_smooth = smooth_function( sample );
				cost_neighbor_not_so_smooth = not_so_smooth_function( sample );
		
				if( cost_smooth >= cost_neighbor_smooth )
					local_smooth = false;

				if( cost_not_so_smooth >= cost_neighbor_not_so_smooth )
					local_not_so_smooth = false;
			}
			
			sample[v] = backup;
		}

		if( local_smooth )
			++lm_smooth;
		
		if( local_not_so_smooth )
			++lm_not_so_smooth;
	}

	smooth = -lm_smooth;
	not_so_smooth = -lm_not_so_smooth;	
}

int main()
{
	double smooth, not_so_smooth;

	auto random = compute_ECL( 9, smooth, not_so_smooth );

	cout << "ECL for a smooth function: " << smooth
	     << "\nECL for a not-so-smooth function: " << not_so_smooth
	     << "\nECL for a random function: " << random << "\n";


	random = compute_local_correlation( 9, smooth, not_so_smooth );

	cout << "\nLocal correlation for a smooth function: " << smooth
	     << "\nLocal correlation for a not-so-smooth function: " << not_so_smooth
	     << "\nLocal correlation for a random function: " << random << "\n";

	// sample_local_minimum( 9, smooth, not_so_smooth );

	// cout << "\nSample local minimums for a smooth function: " << smooth
	//      << "\nSample local minimums  for a not-so-smooth function: " << not_so_smooth << "\n";

	return EXIT_SUCCESS;
}
