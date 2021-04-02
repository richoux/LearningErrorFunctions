// Better use compute_costs_map.cpp now

//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <fstream>

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

// Command line arguments manager
#include <argh.h>

#include "../utils/metrics.hpp"
#include "../utils/convert.hpp"


using namespace std;

string constraint;
int nb_vars, max_value;
int number_samplings;
bool has_parameters;
vector<int> random_solutions;
vector<int> random_configurations;
map<string, double> cost_map;
string input_file_path;
ifstream input_file;
string line, string_number;
string output_file_path;
ofstream output_file;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << "-n NB_VARIABLES -i INPUT_FILE -o OUTPUT_FILE\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint.\n"
	     << "-i, --input INPUT_FILE containing sampled configurations.\n"
	     << "-o, --output OUTPUT_FILE\n";
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	argh::parser cmdl( { "-n", "--nb_vars", "-o", "--output", "-i", "--input" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"i", "input"} ) && cmdl( {"o", "output"} ) ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	// if( cmdl( {"i", "input"} ) && cmdl( {"o", "output"} ) )
	// {
	// 	cerr << "You cannot provide both an input file and a Hamming input file at the same time.\n";
	// 	usage( argv );
	// 	return EXIT_FAILURE;
	// }
	
	cmdl( {"n", "nb_vars"} ) >> nb_vars;

	if( cmdl( {"i", "input"} ) )
	{
		cmdl( {"i", "input"} ) >> input_file_path;
		cout << "Loading data from " << input_file_path << "\n";

		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number;
		line_stream >> number_samplings;

		// loading solutions
		for( int i = 0; i < number_samplings; ++i )
		{
			getline( input_file, line );
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				random_solutions.push_back( number );
			}
		}
		
		// loading not solutions
		for( int i = 0; i < number_samplings; ++i )
		{
			getline( input_file, line );
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				random_configurations.push_back( number );
			}
		}
		
		input_file.close();
	}
	// else if( cmdl( {"hi", "hamming_input"} ) )
	// {
	// 	if( !xp )
	// 		cout << "Loading data from " << input_file_path << "\n";

	// 	cmdl( {"hi", "hamming_input"} ) >> input_file_path;
	// 	input_file.open( input_file_path );

	// 	int number;
	// 	int index = 0;
		
	// 	// loading solutions
	// 	for( int i = 0; i < 100; ++i )
	// 	{
	// 		getline( input_file, line );
	// 		auto delimiter = line.find(" : ");
	// 		std::string cost_token = line.substr( 0, delimiter );
	// 		line.erase(0, delimiter + 3 );
			
	// 		stringstream line_stream( line );
	// 		while( line_stream >> string_number )
	// 		{
	// 			stringstream number_stream( string_number );
	// 			number_stream >> number;
	// 			random_solutions.push_back( number );
	// 		}

	// 		cost_map.insert({ convert( random_solutions, index, index + nb_vars ), std::stod( cost_token ) });
	// 		index += nb_vars;
	// 	}		

	// 	input_file.close();
	// }

	cout << "Loading data done. Start estimating Hamming distances.\n";
	cost_map = compute_metric_hamming_only( random_solutions, random_configurations, nb_vars );

	cmdl( {"o", "output"} ) >> output_file_path;
	cout << "Estimation done. Writing it in " << output_file_path << "\n";
	output_file.open( output_file_path );

	output_file << 2*number_samplings << "\n";
	
	for( auto tuple : cost_map )
	{
		auto config = revert( tuple.first );
		auto cost = static_cast<int>( tuple.second );

		output_file << cost << " : ";
		std::copy( config.begin(), config.end(), ostream_iterator<int>( output_file, " " ) );
		output_file << "\n";
	}

	output_file.close();

	return EXIT_SUCCESS;
}
