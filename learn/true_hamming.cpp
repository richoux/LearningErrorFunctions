//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <fstream>
#include <vector>
#include <string>
#include <map>
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
map<string, double> cost_map;
bool test;

randutils::mt19937_rng rng;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|lt|ol|cm} -o OUTPUT_FILE [-n NB_VARIABLES = 100] [-d MAX_VALUE_DOMAIN = NB_VARIABLES] [-p PARAMETERS] [-t COMPLETE_INPUT_FILE]\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-c, --constraint {ad|le|lt|ol|cm}, respectively for AllDiff, Linear equation, Less than, Overlap 1D and Connection minimum.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint. Default is 100.\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN, the maximal value variables can take. Default is NB_VARIABLES.\n"
	     << "-p, --params PARAMETERS, the list of parameters required.\n"
	     << "-o, --output OUTPUT_FILE\n"
	     << "-t, --test COMPLETE_INPUT_FILE containing the full configuration space.\n";
}

void write( int cost, const vector<int>& config )
{
	output_file << cost << " : ";
	std::copy( config.begin(), config.end(), ostream_iterator<int>( output_file, " " ) );
	output_file << "\n";
}

////////////////
// Hamming costs
////////////////

int cost_ad( vector<int> input )
{
	int cost = 0;
	for( int i =0; i < nb_vars; ++i )
	{
		std::transform( input.begin(), input.end(), input.begin(), [](auto& v){ return --v; } );
		cost += std::max<int>( 0, std::count( input.begin(), input.end(), 0 ) - 1 );
	}
	return cost;
}

int cost_le( vector<int> input )
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

// Warning! This is an approximation.
int cost_lt( vector<int> input )
{
	int cost = 0;
	
	for( int i = 0; i < (int)input.size() - 1; ++i )
	{
		int cost_left = 0;
		int cost_right = 0;

		int min_val = 0;
		int max_val = 0;

		int min_j = 0;
		int max_j = 0;
		int cascade_j = 0;
		
		if( input[i] > input[i+1] )
		{
			int j = i+1;
			while( j <= nb_vars - 1 && input[j-1] >= input[j] )
				++j;
			cascade_j = j;

			j = i+1;
			while( j <= nb_vars - 1 && input[i] > input[j] )
			{
				++j;
				++cost_right;
			}

			if( j > nb_vars - 1 )
				max_val = max_value;
			else
				max_val = input[j];

			max_j = j;
			if( !test )
				cout << "j right=" << j;
			
			j = i;
			while( j >= 0 && input[j] > input[i+1] )
			{
				--j;
				++cost_left;
			}

			if( j < 0 )
				min_val = 1;
			else
				min_val = input[j];

			min_j = j;			
			if( !test )
			{
				cout << ", j left=" << j << "\n";
				
				cout << "Config: ";
				std::copy( input.begin(), input.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\nconfig[" << i << "]=" << input[i]
				     << ", config[" << i+1 << "]=" << input[i+1]
				     << ", cost_right=" << cost_right << ", cost_left=" << cost_left
				     << ", min_val=" << min_val << ", max_val=" << max_val
				     << ", min_j=" << min_j << ", max_j=" << max_j << ", cascade_j=" << cascade_j << "\n";
			}

			if( cost_right == cost_left )
			{
				if( max_j >= nb_vars - 1 )
				{
					for( j = 0; j < cost_right; ++j )
						input[ i + 1 + j ] = max_val;
					cost += cost_right;
				}
				else if( min_j <= 0 )
				{
					for( j = 0; j < cost_left; ++j )
						input[ i - j ] = min_val;
					cost += cost_left;
				}
				else 
				{
					for( j = 0; j < cost_right; ++j )
						input[ i + 1 + j ] = max_val;
					cost += cost_right;
				}
			}
			else if( cost_right < cost_left || ( max_j >= nb_vars - 1 && cascade_j == max_j ) )
			{
				for( j = 0; j < cost_right; ++j )
					input[ i + 1 + j ] = max_val;
				cost += cost_right;
			}
			else
			{
				for( j = 0; j < cost_left; ++j )
					input[ i - j ] = min_val;
				cost += cost_left;
			}

			if( !test )
			{
				cout << "new Config: ";
				std::copy( input.begin(), input.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\n\n";
			}
		}
	}

	return cost;
}

int cost_cm( const vector<int>& input )
{
	return std::count_if( input.begin(), input.end(), [](auto& v){ return v < params_value; } );
}

// Warning! This is an approximation.
int cost_ol( const vector<int>& input )
{
	int cost = 0;

	for( int i = 0; i < (int)input.size(); ++i )
		for( int j = 0; j < (int)input.size(); ++j )
			if( i != j && input[j] >= input[i] + params_value  )
				++cost;

	int series = 0;
	for( int i = 1; i < nb_vars; ++i )
		series += i;
	
	return std::abs( cost - series );	
}

////////////////
// Constraints
////////////////

void ad()
{
	if( test )
	{
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			auto cost = cost_ad( config );
			if( cost != static_cast<int>( tuple.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
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
			write( 0, start_config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			rng.shuffle( start_config );
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int nb_changes = rng.uniform( 1, 30 );
			for( int j = 0; j < nb_changes; ++j )
				config[ rng.uniform( 0, nb_vars - 1 ) ] = rng.uniform( 1, nb_vars );

			write( cost_ad( config ), config );
		}	
	}
}

void le()
{
	if( test )
	{
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			auto cost = cost_le( config );
			if( cost != static_cast<int>( tuple.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> config( nb_vars );
		rng.generate( config, 1, max_value );
		params_value = std::accumulate( config.begin(), config.end(), 0 );

		output_file.open( output_file_path );
		output_file << "20000\n";
		write( 0, config );

		for( int i = 0; i < 9999; ++i )
		{
			int index = rng.uniform( 0, nb_vars - 2 );
			if( config[ index ] < max_value && config[ index + 1 ] > 1 )
			{
				++config[ index ];
				--config[ index + 1 ];
			}
			write( 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			int nb_changes = rng.uniform( 1, 30 );
			for( int j = 0; j < nb_changes; ++j )
				config[ rng.uniform( 0, nb_vars - 1 ) ] = rng.uniform( 1, nb_vars );

			write( cost_le( config ), config );
		}
	}
}

void lt()
{
	if( test )
	{
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			auto cost = cost_lt( config );
			if( cost != static_cast<int>( tuple.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
			}
		}
	}
	else
	{
		vector<int> start_config( nb_vars );
		vector<int> config( nb_vars );

		std::iota( start_config.begin(), start_config.end(), 1 );
		output_file.open( output_file_path );
		write( 0, start_config );

		for( int i = 0; i < 24; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
			int nb_changes = rng.uniform( 1, 30 );
			for( int j = 0; j < nb_changes; ++j )
			{
				int index = rng.uniform( 0, nb_vars - 2 );
				config[ index ] = config[ index + 1 ];
			}
			write( 0, config );
		}

		// cost 1
 		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 2 );
			config[ index ] = config[ index + 1 ] + 1;

			write( 1, config );
		}

		// cost 2
 		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 4 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;

			write( 2, config );
		}

		// cost 3
 		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 6 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;

			write( 3, config );
		}

		// cost 4
 		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 8 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;
			config[ index + 6 ] = config[ index + 7 ] + 1;

			write( 4, config );
		}

		// cost 5
 		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 10 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;
			config[ index + 6 ] = config[ index + 7 ] + 1;
			config[ index + 8 ] = config[ index + 9 ] + 1;

			write( 5, config );
		}

		// cost 6
		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 12 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;
			config[ index + 6 ] = config[ index + 7 ] + 1;
			config[ index + 8 ] = config[ index + 9 ] + 1;
			config[ index + 10 ] = config[ index + 11 ] + 1;

			write( 6, config );
		}

		// cost 7
		for( int i = 0; i < 10; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 14 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;
			config[ index + 6 ] = config[ index + 7 ] + 1;
			config[ index + 8 ] = config[ index + 9 ] + 1;
			config[ index + 10 ] = config[ index + 11 ] + 1;
			config[ index + 12 ] = config[ index + 13 ] + 1;

			write( 7, config );
		}

		// cost 8
		for( int i = 0; i < 5; ++i )
		{
			std::copy( start_config.begin(), start_config.end(), config.begin() );
		
			int index = rng.uniform( 0, nb_vars - 16 );
			config[ index ] = config[ index + 1 ] + 1;
			config[ index + 2 ] = config[ index + 3 ] + 1;
			config[ index + 4 ] = config[ index + 5 ] + 1;
			config[ index + 6 ] = config[ index + 7 ] + 1;
			config[ index + 8 ] = config[ index + 9 ] + 1;
			config[ index + 10 ] = config[ index + 11 ] + 1;
			config[ index + 12 ] = config[ index + 13 ] + 1;
			config[ index + 14 ] = config[ index + 15 ] + 1;

			write( 8, config );
		}

		// cout << "/////////////////\n";
		// config = {8,8,8,7,7,5,6};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {2,1,8,6,7,3,4,2,1};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {4,3,1,1,2};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";
	
		// config = {2,2,1,3,1};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {4,1,4,2,3};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {3,4,2,1,5};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {1,3,3,2,1};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {2,1,8,1,1};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {3,3,2,1,3};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";

		// config = {4,4,3,2,1};
		// cout << cost_lt( config ) << " : ";
		// std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
		// cout << "\n";
	}
}

void cm()
{
	if( test )
	{
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			auto cost = cost_cm( config );
			if( cost != static_cast<int>( tuple.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
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
			write( 0, config );
		}

		for( int i = 0; i < 10000; ++i )
		{
			rng.generate( config, 1, max_value );
			int nb_changes = rng.uniform( 1, 30 );
			for( int j = 0; j < nb_changes; ++j )
			{
				int bad = rng.uniform( 1, params_value - 1 );
				int index = rng.uniform( 0, nb_vars - 1 );
				config[ index ] = bad;
			}

			write( cost_cm( config ), config );
		}
	}
}

void ol()
{
	if( test )
	{
		for( auto tuple : cost_map )
		{
			auto config = revert( tuple.first );
			auto cost = cost_ol( config );
			if( cost != static_cast<int>( tuple.second ) )
			{
				cout << "config: ";
				std::copy( config.begin(), config.end(), std::ostream_iterator<int>( cout, " ") );
				cout << "\ncompared Hamming=" << static_cast<int>( tuple.second ) << ", computed Hamming=" << cost << "\n\n";
			}
		}
	}
	else
	{
		
	}
}

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
		cost_map = compute_metric_hamming_only( random_solutions, random_configurations, nb_vars );
	}
	
	if( !( cmdl( {"c", "constraint"} ) >> constraint )
	    ||
	    ( constraint.compare("ad") != 0
	      && constraint.compare("le") != 0
	      && constraint.compare("lt") != 0
	      && constraint.compare("ol") != 0
	      && constraint.compare("cm") != 0 ) )
	{
		cerr << "Must provide a valid constraint among ad, le, lt, ol and cm. You provided '" << cmdl( {"c", "constraint"} ).str() << "'\n";
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
		
		if( constraint.compare("lt") == 0 )
		{
			cout << "Constraint: Less than.\n";
			lt();
		}
		
		if( constraint.compare("ol") == 0 )
		{
			cout << "Constraint: Overlap 1D.\n";
			ol();
		}
		
		if( constraint.compare("cm") == 0 )
		{
			cout << "Constraint: Connection Minimum (greater-than version).\n";
			cm();
		}
	}

	return EXIT_SUCCESS;
}
