// To create files in the hamming folder

//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iterator>

// Command line arguments manager
#include <argh.h>

// code from the CFN version
//-----------------------------------------------------------------------------

#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"

using namespace std;

int nb_vars, max_value;
string constraint;
string output_file_path;
ofstream output_file;
int params_value;
string input_file_path;
ifstream input_file;
string line, string_number;
vector<int> random_solutions;
vector<int> random_configurations;
map<string, pair<double,double>> cost_map;
bool test;

randutils::mt19937_rng rng;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|ll|lg|cm} -o OUTPUT_FILE [-n NB_VARIABLES = 100] [-d MAX_VALUE_DOMAIN = NB_VARIABLES] [-p PARAMETERS] [-t COMPLETE_INPUT_FILE]\n"
	     << "This program aims to compute metrics over large spaces of constraints for which we know how to exactly compute the metrics (like AllDifferent for instance).\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-c, --constraint {ad|le|ll|lg|cm}, respectively for AllDiff, Linear equation, Linear inequation <=, Linear inequation >= and Connection minimum.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint. Default is 100.\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN, the maximal value variables can take. Default is NB_VARIABLES.\n"
	     << "-p, --params PARAMETERS, the list of parameters required.\n"
	     << "-o, --output OUTPUT_FILE\n"
	     << "-t, --test COMPLETE_INPUT_FILE containing the full configuration space.\n";
}

void write( int cost_hamming, int cost_manhattan, const vector<int>& config )
{
	output_file << cost_hamming << " " << cost_manhattan << " : ";
	std::copy( config.begin(), config.end(), ostream_iterator<int>( output_file, " " ) );
	output_file << "\n";
}

////////////////
// Hamming costs
////////////////

int cost_hamming_ad( vector<int> input )
{
	int cost = 0;
	for( int i =0; i < max_value; ++i )
	{
		std::transform( input.begin(), input.end(), input.begin(), [](auto& v){ return --v; } );
		cost += std::max<int>( 0, std::count( input.begin(), input.end(), 0 ) - 1 );
	}
	return cost;
}

int cost_hamming_le( vector<int> input )
{
	int cost = 0;

	auto sum = std::accumulate( input.begin(), input.end(), 0 );
	auto it = input.begin();
	
	while( sum != params_value )
	{
		if( sum < params_value )
			it = std::min_element( input.begin(), input.end() );
		else
			it = std::max_element( input.begin(), input.end() );

		auto diff = std::abs( sum - params_value );
		if( sum < params_value )
		{
			if( diff <= max_value - *it )
				*it += diff;
			else
				*it = max_value;
		}
		else
		{
			if( diff < *it )
				*it -= diff;
			else
				*it = 1;
		}

		++cost;
		sum = std::accumulate( input.begin(), input.end(), 0 );		
	};	
	
	return cost;
}

int cost_hamming_ll( vector<int> input )
{
	int cost = 0;

	auto sum = std::accumulate( input.begin(), input.end(), 0 );
	auto it = input.begin();
	
	while( sum > params_value )
	{
		it = std::max_element( input.begin(), input.end() );
		*it = 1;

		++cost;
		sum = std::accumulate( input.begin(), input.end(), 0 );		
	};	
	
	return cost;
}

int cost_hamming_lg( vector<int> input )
{
	int cost = 0;

	auto sum = std::accumulate( input.begin(), input.end(), 0 );
	auto it = input.begin();
	
	while( sum < params_value )
	{
		it = std::min_element( input.begin(), input.end() );
		*it = max_value;

		++cost;
		sum = std::accumulate( input.begin(), input.end(), 0 );		
	};	
	
	return cost;
}

// Warning! This is an approximation.
// int cost_hamming_lt( vector<int> input )
// {
// 	int cost = 0;
	
// 	for( int i = 0; i < (int)input.size() - 1; ++i )
// 	{
// 		int cost_hamming_left = 0;
// 		int cost_right = 0;

// 		int min_val = 0;
// 		int max_val = 0;

// 		int min_j = 0;
// 		int max_j = 0;
// 		int cascade_j = 0;
		
// 		if( input[i] > input[i+1] )
// 		{
// 			int j = i+1;
// 			while( j <= nb_vars - 1 && input[j-1] >= input[j] )
// 				++j;
// 			cascade_j = j;

// 			j = i+1;
// 			while( j <= nb_vars - 1 && input[i] > input[j] )
// 			{
// 				++j;
// 				++cost_right;
// 			}

// 			if( j > nb_vars - 1 )
// 				max_val = max_value;
// 			else
// 				max_val = input[j];

// 			max_j = j;
// 			if( !test )
// 				cout << "j right=" << j;
			
// 			j = i;
// 			while( j >= 0 && input[j] > input[i+1] )
// 			{
// 				--j;
// 				++cost_hamming_left;
// 			}

// 			if( j < 0 )
// 				min_val = 1;
// 			else
// 				min_val = input[j];

// 			min_j = j;			
// 			if( !test )
// 			{
// 				cout << ", j left=" << j << "\n";
				
// 				cout << "Config: ";
// 				std::copy( input.begin(), input.end(), std::ostream_iterator<int>( cout, " ") );
// 				cout << "\nconfig[" << i << "]=" << input[i]
// 				     << ", config[" << i+1 << "]=" << input[i+1]
// 				     << ", cost_right=" << cost_right << ", cost_hamming_left=" << cost_hamming_left
// 				     << ", min_val=" << min_val << ", max_val=" << max_val
// 				     << ", min_j=" << min_j << ", max_j=" << max_j << ", cascade_j=" << cascade_j << "\n";
// 			}

// 			if( cost_right == cost_hamming_left )
// 			{
// 				if( max_j >= nb_vars - 1 )
// 				{
// 					for( j = 0; j < cost_right; ++j )
// 						input[ i + 1 + j ] = max_val;
// 					cost += cost_right;
// 				}
// 				else if( min_j <= 0 )
// 				{
// 					for( j = 0; j < cost_hamming_left; ++j )
// 						input[ i - j ] = min_val;
// 					cost += cost_hamming_left;
// 				}
// 				else 
// 				{
// 					for( j = 0; j < cost_right; ++j )
// 						input[ i + 1 + j ] = max_val;
// 					cost += cost_right;
// 				}
// 			}
// 			else if( cost_right < cost_hamming_left || ( max_j >= nb_vars - 1 && cascade_j == max_j ) )
// 			{
// 				for( j = 0; j < cost_right; ++j )
// 					input[ i + 1 + j ] = max_val;
// 				cost += cost_right;
// 			}
// 			else
// 			{
// 				for( j = 0; j < cost_hamming_left; ++j )
// 					input[ i - j ] = min_val;
// 				cost += cost_hamming_left;
// 			}

// 			if( !test )
// 			{
// 				cout << "new Config: ";
// 				std::copy( input.begin(), input.end(), std::ostream_iterator<int>( cout, " ") );
// 				cout << "\n\n";
// 			}
// 		}
// 	}

// 	return cost;
// }

int cost_hamming_cm( const vector<int>& input )
{
	return std::count_if( input.begin(), input.end(), [](auto& v){ return v < params_value; } );
}

// Warning! This is an approximation.
// int cost_hamming_ol( const vector<int>& input )
// {
// 	int cost = 0;

// 	for( int i = 0; i < (int)input.size(); ++i )
// 		for( int j = 0; j < (int)input.size(); ++j )
// 			if( i != j && input[j] >= input[i] + params_value  )
// 				++cost;

// 	int series = 0;
// 	for( int i = 1; i < nb_vars; ++i )
// 		series += i;
	
// 	return std::abs( cost - series );	
// }

//////////////////
// Manhattan costs
//////////////////

int cost_manhattan_ad( const vector<int>& input )
{
	int cost = 0;
	vector<int> vec_counter( max_value, 0 );
	
	for( auto value : input )
		++vec_counter[ value ];

	for( int i = 0 ; i < max_value - 1 ; ++i )
	{
		if( vec_counter[i] == 0 )
		{
			int j = i + 1;
			while( vec_counter[j] < 1 )
				++j;

			cost += ( j - i );
			--vec_counter[j];
			vec_counter[i] = 1;
		}

		if( vec_counter[i] > 1 )
		{
			int j = i + 1;
			while( vec_counter[j] != 0 )
				++j;

			cost += ( j - i );
			vec_counter[j] = 1;
			--vec_counter[i];
			--i;
		}		
	}
	
	return cost;
}

int cost_manhattan_le( const vector<int>& input )
{
	int sum = 0;
	for( auto value : input )
		sum += value;
	return std::abs( sum - params_value );
}

int cost_manhattan_ll( const vector<int>& input )
{
	int sum = 0;
	for( auto value : input )
		sum += value;
	return std::max( 0, sum - params_value );
}

int cost_manhattan_lg( const vector<int>& input )
{
	int sum = 0;
	for( auto value : input )
		sum += value;
	return std::max( 0, params_value - sum );
}

int cost_manhattan_cm( const vector<int>& input )
{
	int cost = 0;
	
	for( auto value : input )
		if( value < params_value )
			cost += ( params_value - value );
	
	return cost;
}

////////////////
// Constraints
////////////////

void ad()
{
	if( test )
	{
		int cost;
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			cost = cost_hamming_ad( config );

			if( cost != static_cast<int>( tuple.second.first ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second.first ) << ", computed Hamming=" << cost << "\n\n";
			}

			cost = cost_manhattan_ad( config );
			
			if( cost != static_cast<int>( tuple.second.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Manhattan=" << static_cast<int>( tuple.second.second ) << ", computed Manhattan=" << cost << "\n\n";
			}				
		}
	}
	else
	{
		vector<int> start_config( nb_vars );
		vector<int> config( nb_vars );

		std::iota( start_config.begin(), start_config.end(), 1 );
		output_file.open( output_file_path );

		output_file << "20000\n";
		
		for( int i = 0; i < 10000; ++i )
		{
			rng.shuffle( start_config );
			write( 0, 0, start_config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			rng.shuffle( start_config );
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int nb_changes = rng.uniform( 2, 30 );
			for( int j = 0; j < nb_changes; ++j )
				config[ rng.uniform( 0, nb_vars - 1 ) ] = rng.uniform( 1, nb_vars );

			write( cost_hamming_ad( config ), cost_manhattan_ad( config ), config );
		}
	}
}

void le()
{
	if( test )
	{
		int cost;
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );

			cost = cost_hamming_le( config );
			
			if( cost != static_cast<int>( tuple.second.first ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second.first ) << ", computed Hamming=" << cost << "\n\n";
			}

			cost = cost_manhattan_le( config );
			
			if( cost != static_cast<int>( tuple.second.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Manhattan=" << static_cast<int>( tuple.second.second ) << ", computed Manhattan=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> config( nb_vars );
		rng.generate( config, 1, max_value );
		auto sum = std::accumulate( config.begin(), config.end(), 0 );
		double diff = std::abs( sum - params_value );
		auto mean = std::ceil( diff / nb_vars );
		bool need_to_increase = ( sum < params_value );
		
		while( sum != params_value )
		{
			auto index = rng.uniform( 0, nb_vars - 1 );
			if( need_to_increase )
			{
				if( config[ index ] < max_value - ( mean * 2 ) )
					config[ index ] += ( mean * 2 );
				else
					if( config[ index ] < max_value - mean )
						config[ index ] += mean;
					else
						if( config[ index ] < max_value )
							++config[ index ];
			}
			else
			{
				if( config[ index ] > mean * 2 )
					config[ index ] -= ( mean * 2 );
				else
					if( config[ index ] > mean )
						config[ index ] -= mean;
					else
						if( config[ index ] > 1 )
							--config[ index ];
			}
			sum = std::accumulate( config.begin(), config.end(), 0 );
			need_to_increase = ( sum < params_value );				
		}

		output_file.open( output_file_path );
		output_file << "20000\n";
		write( 0, 0, config );

		for( int i = 0; i < 9999; ++i )
		{
			int index = rng.uniform( 0, nb_vars - 2 );
			if( config[ index ] < max_value && config[ index + 1 ] > 1 )
			{
				++config[ index ];
				--config[ index + 1 ];
			}
			write( 0, 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			int nb_changes = rng.uniform( 2, 30 );
			for( int j = 0; j < nb_changes; ++j )
				config[ rng.uniform( 0, nb_vars - 1 ) ] = rng.uniform( 1, nb_vars );

			write( cost_hamming_le( config ), cost_manhattan_le( config ), config );
		}
	}
}

void ll()
{
	if( test )
	{
		int cost;
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );

			cost = cost_hamming_ll( config );
			
			if( cost != static_cast<int>( tuple.second.first ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second.first ) << ", computed Hamming=" << cost << "\n\n";
			}

			cost = cost_manhattan_ll( config );
			
			if( cost != static_cast<int>( tuple.second.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Manhattan=" << static_cast<int>( tuple.second.second ) << ", computed Manhattan=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> config( nb_vars );
		vector<int> copy_config( nb_vars );
		rng.generate( config, 1, max_value );

		auto sum = std::accumulate( config.begin(), config.end(), 0 );
		double diff = std::abs( sum - params_value );
		auto mean = std::ceil( diff / nb_vars );
		
		while( sum > params_value )
		{
			auto index = rng.uniform( 0, nb_vars - 1 );

			if( config[ index ] > mean * 2 )
				config[ index ] -= ( mean * 2 );
			else
				if( config[ index ] > mean )
					config[ index ] -= mean;
				else
					if( config[ index ] > 1 )
						--config[ index ];

			sum = std::accumulate( config.begin(), config.end(), 0 );
		}

		std::copy( config.begin(), config.end(), copy_config.begin() );

		output_file.open( output_file_path );
		output_file << "20000\n";

		for( int i = 0; i < 10000; ++i )
		{
			std::copy( copy_config.begin(), copy_config.end(), config.begin() );
			rng.shuffle( config );
			
			int nb_changes = rng.uniform( 2, 30 );
			
			for( int j = 0; j < nb_changes; ++j )
			{
				auto index = rng.uniform( 0, nb_vars - 1 );
				config[ index ] = rng.uniform( 1, config[ index ] );
			}
			
			write( 0, 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			std::copy( copy_config.begin(), copy_config.end(), config.begin() );
			rng.shuffle( config );

			int nb_changes = rng.uniform( 2, 30 );

			for( int j = 0; j < nb_changes; ++j )
			{
				int index;
				do
				{
					index = rng.uniform( 0, nb_vars - 1 );
				} while( config[ index ] == max_value );
				
				config[ index ] = rng.uniform( config[ index ] + 1, max_value );
			}
			
			write( cost_hamming_ll( config ), cost_manhattan_ll( config ), config );
		}
	}
}

void lg()
{
	if( test )
	{
		int cost;
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );

			cost = cost_hamming_lg( config );
			
			if( cost != static_cast<int>( tuple.second.first ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second.first ) << ", computed Hamming=" << cost << "\n\n";
			}

			cost = cost_manhattan_lg( config );
			
			if( cost != static_cast<int>( tuple.second.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Manhattan=" << static_cast<int>( tuple.second.second ) << ", computed Manhattan=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> config( nb_vars );
		vector<int> copy_config( nb_vars );
		rng.generate( config, 1, max_value );
				
		auto sum = std::accumulate( config.begin(), config.end(), 0 );
		double diff = std::abs( sum - params_value );
		auto mean = std::ceil( diff / nb_vars );
		
		while( sum < params_value )
		{
			auto index = rng.uniform( 0, nb_vars - 1 );

			if( config[ index ] < max_value - ( mean * 2 ) )
				config[ index ] += ( mean * 2 );
			else
				if( config[ index ] < max_value - mean )
					config[ index ] += mean;
				else
					if( config[ index ] < max_value )
						++config[ index ];

			sum = std::accumulate( config.begin(), config.end(), 0 );
		}

		std::copy( config.begin(), config.end(), copy_config.begin() );

		output_file.open( output_file_path );
		output_file << "20000\n";

		for( int i = 0; i < 10000; ++i )
		{
			std::copy( copy_config.begin(), copy_config.end(), config.begin() );
			rng.shuffle( config );
			
			int nb_changes = rng.uniform( 2, 30 );
			
			for( int j = 0; j < nb_changes; ++j )
			{
				auto index = rng.uniform( 0, nb_vars - 1 );
				config[ index ] = rng.uniform( config[ index ], max_value );
			}
			
			write( 0, 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			std::copy( copy_config.begin(), copy_config.end(), config.begin() );
			rng.shuffle( config );

			int nb_changes = rng.uniform( 2, 30 );

			for( int j = 0; j < nb_changes; ++j )
			{
				int index;
				do
				{
					index = rng.uniform( 0, nb_vars - 1 );
				} while( config[ index ] == 1 );
				
				config[ index ] = rng.uniform( 1, config[ index ] - 1 );
			}
			
			write( cost_hamming_lg( config ), cost_manhattan_lg( config ), config );
		}
	}
}

// void lt()
// {
// 	if( test )
// 	{
// 		for( auto tuple : cost_map )
// 		{
// 			auto config = revert( tuple.first );
// 			auto cost = cost_hamming_lt( config );
// 			if( cost != static_cast<int>( tuple.second ) )
// 			{
// 				cout << "config: ";
// 				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
// 			}
// 		}
// 	}
// 	else
// 	{
// 		vector<int> start_config( nb_vars );
// 		vector<int> config( nb_vars );

// 		std::iota( start_config.begin(), start_config.end(), 1 );
// 		output_file.open( output_file_path );
// 		write( 0, start_config );

// 		for( int i = 0; i < 24; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
// 			int nb_changes = rng.uniform( 2, 30 );
// 			for( int j = 0; j < nb_changes; ++j )
// 			{
// 				int index = rng.uniform( 0, nb_vars - 2 );
// 				config[ index ] = config[ index + 1 ];
// 			}
// 			write( 0, config );
// 		}

// 		// cost 1
//  		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 2 );
// 			config[ index ] = config[ index + 1 ] + 1;

// 			write( 1, config );
// 		}

// 		// cost 2
//  		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 4 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;

// 			write( 2, config );
// 		}

// 		// cost 3
//  		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 6 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;

// 			write( 3, config );
// 		}

// 		// cost 4
//  		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 8 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;
// 			config[ index + 6 ] = config[ index + 7 ] + 1;

// 			write( 4, config );
// 		}

// 		// cost 5
//  		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 10 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;
// 			config[ index + 6 ] = config[ index + 7 ] + 1;
// 			config[ index + 8 ] = config[ index + 9 ] + 1;

// 			write( 5, config );
// 		}

// 		// cost 6
// 		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 12 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;
// 			config[ index + 6 ] = config[ index + 7 ] + 1;
// 			config[ index + 8 ] = config[ index + 9 ] + 1;
// 			config[ index + 10 ] = config[ index + 11 ] + 1;

// 			write( 6, config );
// 		}

// 		// cost 7
// 		for( int i = 0; i < 10; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 14 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;
// 			config[ index + 6 ] = config[ index + 7 ] + 1;
// 			config[ index + 8 ] = config[ index + 9 ] + 1;
// 			config[ index + 10 ] = config[ index + 11 ] + 1;
// 			config[ index + 12 ] = config[ index + 13 ] + 1;

// 			write( 7, config );
// 		}

// 		// cost 8
// 		for( int i = 0; i < 5; ++i )
// 		{
// 			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
// 			int index = rng.uniform( 0, nb_vars - 16 );
// 			config[ index ] = config[ index + 1 ] + 1;
// 			config[ index + 2 ] = config[ index + 3 ] + 1;
// 			config[ index + 4 ] = config[ index + 5 ] + 1;
// 			config[ index + 6 ] = config[ index + 7 ] + 1;
// 			config[ index + 8 ] = config[ index + 9 ] + 1;
// 			config[ index + 10 ] = config[ index + 11 ] + 1;
// 			config[ index + 12 ] = config[ index + 13 ] + 1;
// 			config[ index + 14 ] = config[ index + 15 ] + 1;

// 			write( 8, config );
// 		}

// 		// cout << "/////////////////\n";
// 		// config = {8,8,8,7,7,5,6};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {2,1,8,6,7,3,4,2,1};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {4,3,1,1,2};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";
	
// 		// config = {2,2,1,3,1};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {4,1,4,2,3};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {3,4,2,1,5};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {1,3,3,2,1};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {2,1,8,1,1};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {3,3,2,1,3};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";

// 		// config = {4,4,3,2,1};
// 		// cout << cost_hamming_lt( config ) << " : ";
// 		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 		// cout << "\n";
// 	}
// }

void cm()
{
	if( test )
	{
		int cost;
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );

			cost = cost_hamming_cm( config );
			
			if( cost != static_cast<int>( tuple.second.first ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second.first ) << ", computed Hamming=" << cost << "\n\n";
			}

			cost = cost_manhattan_cm( config );
			
			if( cost != static_cast<int>( tuple.second.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Manhattan=" << static_cast<int>( tuple.second.second ) << ", computed Manhattan=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> config( nb_vars );

		output_file.open( output_file_path );
		output_file << "20000\n";

		for( int i = 0; i < 10000; ++i )
		{
			rng.generate( config, 1, max_value );
			std::transform( config.begin(),
			                config.end(),
			                config.begin(),
			                [&](auto& c){ return c < params_value ? rng.uniform( params_value, max_value ) : c; } );
			write( 0, 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			rng.generate( config, 1, max_value );
			int nb_changes = rng.uniform( 2, 30 );
			for( int j = 0; j < nb_changes; ++j )
				config[ rng.uniform( 0, nb_vars - 1 ) ] = rng.uniform( 1, params_value - 1 );

			write( cost_hamming_cm( config ), cost_manhattan_cm( config ), config );
		}
	}
}

// void ol()
// {
// 	if( test )
// 	{
// 		for( auto tuple : cost_map )
// 		{
// 			auto config = revert( tuple.first );
// 			auto cost = cost_hamming_ol( config );
// 			if( cost != static_cast<int>( tuple.second ) )
// 			{
// 				cout << "config: ";
// 				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
// 				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
// 			}
// 		}
// 	}
// 	else
// 	{
		
// 	}
// }

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	argh::parser cmdl( { "-c", "--constraint", "-o", "--output", "-n", "--nb_vars", "-d", "--max_domain", "-p", "--params", "-t", "--test" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !cmdl( {"o", "output"} ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	if( cmdl( {"t", "test"} ) )
		test = true;
	else
		test = false;

	cmdl( {"o", "output"} ) >> output_file_path;	
	cmdl( {"n", "nb_vars"}, 100 ) >> nb_vars;
	cmdl( {"d", "max_domain"}, nb_vars) >> max_value;
	cmdl( {"p", "params"}, 1) >> params_value;

	if( test )
	{
		cout << "Loading data from " << input_file_path << "\n";

		cmdl( {"t", "test"} ) >> input_file_path;
		input_file.open( input_file_path );

		int number;
		
		// loading solutions/configurations
		while( getline( input_file, line ) )
		{
			auto delimiter = line.find(" : ");
			std::string solution_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 3 );
			
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				if( solution_token.compare("1") == 0 )
					random_solutions.push_back( number );
				else
					random_configurations.push_back( number );					
			}
		}		

		input_file.close();
		cost_map = compute_metric_hamming_and_manhattan( random_solutions, random_configurations, nb_vars );
	}
	
	if( !( cmdl( {"c", "constraint"} ) >> constraint )
	    ||
	    ( constraint.compare("ad") != 0
	      && constraint.compare("le") != 0
	      && constraint.compare("ll") != 0
	      && constraint.compare("lg") != 0
	      // && constraint.compare("lt") != 0
	      // && constraint.compare("ol") != 0
	      && constraint.compare("cm") != 0 ) )
	{
		cerr << "Must provide a valid constraint among ad, le, ll, lg and cm. You provided '" << cmdl( {"c", "constraint"} ).str() << "'\n";
		usage( argv );
		return EXIT_FAILURE;
	}
	else
	{
		if( constraint.compare("ad") == 0 )
		{
			cout << "Constraint: AllDiff.\n";
			ad();
		}
		
		if( constraint.compare("le") == 0 )
		{
			cout << "Constraint: Linear equation.\n";
			le();
		}
		
		if( constraint.compare("ll") == 0 )
		{
			cout << "Constraint: Linear inequation <=.\n";
			ll();
		}
		
		if( constraint.compare("lg") == 0 )
		{
			cout << "Constraint: Linear inequation >=.\n";
			lg();
		}
		
		// if( constraint.compare("lt") == 0 )
		// {
		// 	cout << "Constraint: Less than.\n";
		// 	lt();
		// }
		
		// if( constraint.compare("ol") == 0 )
		// {
		// 	cout << "Constraint: Overlap 1D.\n";
		// 	ol();
		// }
		
		if( constraint.compare("cm") == 0 )
		{
			cout << "Constraint: Connection Minimum (greater-than version).\n";
			cm();
		}
	}

	return EXIT_SUCCESS;
}
