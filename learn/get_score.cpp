// To compute the score on test sets of a specific function

//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <sstream>

#include <vector>
#include <string>
#include <map>
#include <algorithm>

// Command line arguments manager
#include <argh.h>

// code from the CFN version
//-----------------------------------------------------------------------------
#include "function_to_learn_icn.hpp" // for number_functions

#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"
#include "../utils/random_draw.hpp"
#include "../utils/convert.hpp"
#include "../utils/print.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

using namespace std;

string constraint;
int nb_vars, max_value;
int samplings;
bool has_parameters;
vector<int> random_solutions;
vector<int> random_configurations;
unique_ptr<Concept> concept;
map<string, double> cost_map;
vector<double> params;
double params_value;
bool latin_sampling;
string input_file_path;
ifstream input_file;
ifstream input_costs_file;
string line, string_number;
bool xp;
bool verbose;
int near_solution;
bool debug;
string function_representation;
vector<int> cost_function;

randutils::mt19937_rng rng_utils;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -s NUMBER_SAMPLINGS -f FUNCTION [-p PARAMETERS] [-l] [--xp]\n"
	     << "   OR: " << argv[0] << " -c {ad|le|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -f FUNCTION -i INPUT_FILE -hi HAMMING_INPUT_FILE [-p PARAMETERS] [--xp]\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-c, --constraint {ad|le|lt|ol|cm}, respectively for AllDiff, Linear equation, Less than, Overlap 1D and Connection minimum.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint.\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN, the maximal value variables can take.\n"
	     << "-s, --sampling NUMBER_SAMPLINGS, the number of required solutions and non-solutions.\n"
	     << "-f, --function FUNCTION, the series of bits representing a cost function.\n"
	     << "-i, --input INPUT_FILE containing sampled configurations from the 'spaces' folder.\n"
	     << "-hi, --hamming_input HAMMING_INPUT_FILE containing sampled configurations with their Hamming cost from the 'hamming' folder.\n"
	     << "-p, --params PARAMETERS, the list of parameters required.\n"
	     << "-l, --latin for performing Latin Hypercube samplings instead of Monte Carlo samplings.\n"
	     << "--xp to print on the screen results for experiments only.\n"
	     << "-v, --verbose"
	     << "--debug.\n";
}

bool no_parameter_operations( const vector<int>& weights )
{
	// test t7, t8, t9, t10, t11, t17, c1, c2, c3, c4
	return weights[7] == 0 && weights[8] == 0 && weights[9] == 0 && weights[10] == 0 && weights[11] == 0 && weights[17] == 0 && weights[21] == 0 && weights[22] == 0 && weights[23] == 0 && weights[24] == 0; 
}

double fitness( const vector<int>& weights )
{
	double cost = 0.0;
	
	for( int i = 0; i < (int)random_solutions.size(); i += nb_vars )
	{
		auto f = cost_map.at( convert( random_solutions, i, i + nb_vars ) );
		auto s = g( weights, params, random_solutions, max_value, i, nb_vars );

		if( debug )
		{
			std::copy( random_solutions.begin() + i, random_solutions.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
			cout << "\n";
		}

		cost += std::abs( f - s );

		if( verbose && f != s )
		{
			if( std::abs( f - s ) == 1 )
				++near_solution;
			
			cout << s << " (" << f << ") : ";
			std::copy( random_solutions.begin() + i, random_solutions.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
			cout << "\n";
		}
		
		if( debug )
		{
			cout << "Hamming: " << f << "\n"
			     << "Score:   " << s << "\n\n";
		}
	}
	
	for( int i = 0; i < (int)random_configurations.size(); i += nb_vars )
	{
		auto f = cost_map.at( convert( random_configurations, i, i + nb_vars ) );
		auto s = g( weights, params, random_configurations, max_value, i, nb_vars );

		if( debug )
		{
			std::copy( random_configurations.begin() + i, random_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
			cout << "\n";
		}

		cost += std::abs( f - s );

		if( verbose && f != s )
		{
			if( std::abs( f - s ) == 1 )
				++near_solution;
			
			cout << s << " (" << f << ") : ";
			std::copy( random_configurations.begin() + i, random_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
			cout << "\n";
		}

		if( debug )
		{
			cout << "Hamming: " << f << "\n"
			     << "Score:   " << s << "\n\n";
		}
	}
	
	return cost;
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-f", "--function", "-s", "--sampling", "-i", "--input", "-hi", "--hamming_input", "-p", "--params" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"d", "max_domain"} ) && cmdl( {"f", "function"} ) ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	if( cmdl( {"i", "input"} ) && cmdl( {"hi", "hamming_input"} ) )
	{
		cerr << "You cannot provide both an input file and a Hamming input file at the same time.\n";
		usage( argv );
		return EXIT_FAILURE;
	}

	if( cmdl[ {"-v", "--verbose"} ] )
		verbose = true;
	else
		verbose = false;
	near_solution = 0;
	
	cmdl( {"n", "nb_vars"}, 9) >> nb_vars;
	cmdl( {"d", "max_domain"}, 9) >> max_value;
	cmdl( {"f", "function"} ) >> function_representation;
	cmdl( {"s", "sampling"}, 100) >> samplings;

	for( const char& c : function_representation )
		cost_function.push_back( stoi( std::string(1, c) ) );
	
	if( cmdl( {"p", "params"} ) )
		has_parameters = true;
	else
		has_parameters = false;
	cmdl( {"p", "params"}, 1.0 ) >> params_value;
	params = vector<double>( nb_vars, params_value );

	if( cmdl[ { "--xp" } ] )
		xp = true;
	else
		xp = false;

	if( cmdl[ { "--debug" } ] )
		debug = true;
	else
		debug = false;

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
			if( !xp )
				cout << "Constraint: AllDiff.\n";
			concept = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			if( !xp )
				cout << "Constraint: Linear equation.\n";
			concept = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}
		
		if( constraint.compare("lt") == 0 )
		{
			if( !xp )
				cout << "Constraint: Less than.\n";
			concept = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			if( !xp )
				cout << "Constraint: Overlap 1D.\n";
			concept = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			if( !xp )
				cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}
	
	if( cmdl[ { "-l", "--latin" } ] )
		latin_sampling = true;
	else
		latin_sampling = false;

	if( cmdl( {"i", "input"} ) )
	{
		cmdl( {"i", "input"} ) >> input_file_path;

		if( !xp )
			cout << "Loading data from " << input_file_path << "\n";

		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number_samplings;
		int number;
		line_stream >> number_samplings;
		samplings = number_samplings * 2;
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

		std::string input_costs_file_path = input_file_path.substr( 0, input_file_path.length() - 4 ) + std::string("_costs.txt");
		input_costs_file.open( input_costs_file_path );
		while( getline( input_costs_file, line ) )
		{
			auto delimiter = line.find(" ");
			std::string solution_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 1 );
			stringstream line_stream( line );
			line_stream >> number;
			cost_map.emplace( solution_token, number );
		}
		
		input_costs_file.close();
	}
	else if( cmdl( {"hi", "hamming_input"} ) )
	{
		cmdl( {"hi", "hamming_input"} ) >> input_file_path;

		if( !xp )
			cout << "Loading data from " << input_file_path << "\n";
		
		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number_samplings;
		line_stream >> number_samplings;
		samplings = number_samplings;

		int number;
		int index = 0;
		
		// loading solutions
		for( int i = 0; i < number_samplings; ++i )
		{
			getline( input_file, line );
			auto delimiter = line.find(" : ");
			std::string cost_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 3 );
			
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				random_solutions.push_back( number );
			}

			cost_map.insert({ convert( random_solutions, index, index + nb_vars ), std::stod( cost_token ) });
			index += nb_vars;
		}		

		input_file.close();
	}
	else		
	{
		if( latin_sampling )
		{
			if( !xp )
				cout << "Perform Latin Hypercube sampling.\n";
			cap_draw( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
		else
		{
			if( !xp )
				cout << "Perform Monte Carlo sampling.\n";
			cap_draw_monte_carlo( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}

		samplings *= 2; // n solutions + n non-solutions 
	}

	if( !cmdl( {"hi", "hamming_input"} ) && !cmdl( {"i", "input"} ) )
		cost_map = compute_metric_hamming_only( random_solutions, random_configurations, nb_vars );
	
	if( !xp )
	{
		int number_solutions, number_non_solutions;
		if( cmdl( {"hi", "hamming_input"} ) )
		{
			number_solutions = random_solutions.size() / ( 2 * nb_vars );
			number_non_solutions = number_solutions;
		}
		else
		{
			number_solutions = random_solutions.size() / nb_vars;
			number_non_solutions = random_configurations.size() / nb_vars;
		}

		auto errors = fitness( cost_function );
		
		cout << "Cumulative error: " << errors
		     << "\nMean error: " << errors / samplings
		     << "\nNormalized mean error: " << ( errors / samplings ) / nb_vars
		     << "\nNumber of variables: " << nb_vars
		     << "\nMax domain value: " << max_value
		     << "\nSampling samplings: " << samplings
		     << "\nNumber of solutions: " << number_solutions << ", density = "
		     << static_cast<double>( number_solutions ) / samplings << "\n";

		if( verbose )
			cout << "Estimations off by 1: " << near_solution << "\n";
		
		print_model( cost_function );
	}
	else
		cout << fitness( cost_function ) << "\n";

	return EXIT_SUCCESS;
}
