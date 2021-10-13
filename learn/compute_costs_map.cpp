// To produce _costs.txt files

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

#include <iostream>
#include <sstream>
#include <fstream>

// Command line option management
#include <argh.h>

#include "../utils/metrics.hpp"

using namespace std;

int nb_vars;
vector<int> random_solutions;
vector<int> random_configurations;
map<string, pair<double,double>> cost_map;
string input_file_path;
ifstream input_file;
string line, string_number;
int number_configurations_in_file;
string output_file_path;
ofstream output_file;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -n NB_VARIABLES {-i|-ci} INPUT_FILE -o OUTPUT_FILE\n"
	     << "Arguments:\n"
	     << "-h, --help\n"
	     << "-n, --nb_vars NB_VARIABLES\n"
	     << "-i, --input INPUT_FILE containing sampled configurations.\n"
	     << "-ci, --complete_input COMPLETE_INPUT_FILE containing the full configuration space.\n"
	     << "-o, --output OUTPUT_FILE\n";
}

int main( int argc, char** argv )
{
	argh::parser cmdl( { "-i", "--input", "-ci", "--complete_input", "-o", "--output", "-n", "--nb_vars" } );
	cmdl.parse( argc, argv );

	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( ( cmdl( {"i", "input"} ) || cmdl( {"ci", "complete_input"} ) ) && cmdl( {"o", "output"} ) && cmdl( {"n", "nb_vars"} ) ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	if( cmdl( {"i", "input"} ) && cmdl( {"ci", "complete_input"} ) )
	{
		cerr << "You cannot provide both an input file and a complete input file at the same time.\n";
		usage( argv );
		return EXIT_FAILURE;
	}

	cmdl( {"n", "nb_vars"}, 9) >> nb_vars;

	if( cmdl( {"i", "input"} ) )
	{
		cmdl( {"i", "input"} ) >> input_file_path;
		cout << "Loading data from " << input_file_path << "\n";
		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number;
		line_stream >> number_configurations_in_file;

		// loading solutions
		for( int i = 0; i < number_configurations_in_file; ++i )
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
		for( int i = 0; i < number_configurations_in_file; ++i )
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

		number_configurations_in_file *= 2;
		input_file.close();
	}
	else //if( cmdl( {"ci", "complete_input"} ) )
	{
		cmdl( {"ci", "complete_input"} ) >> input_file_path;
		cout << "Loading data from " << input_file_path << "\n";
		input_file.open( input_file_path );

		int number;
		
		// loading solutions/configurations
		while( getline( input_file, line ) )
		{
			++number_configurations_in_file;
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
	}

	cost_map = compute_metric_hamming_and_manhattan( random_solutions, random_configurations, nb_vars );

	cmdl( {"o", "output"} ) >> output_file_path;	
	output_file.open( output_file_path );

	for( auto cost : cost_map )
		output_file << cost.first << " " << cost.second.first << " " << cost.second.second << "\n";
	output_file.close();
	
	return EXIT_SUCCESS;
}
