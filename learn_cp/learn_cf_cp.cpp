//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <sstream>

#include <ctime>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <set>
#include <memory>

// Command line arguments manager
#include <argh.h>

#include <ghost/solver.hpp>


#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"
#include "../utils/random_draw.hpp"
#include "../utils/convert.hpp"
#include "../utils/print.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/linear-leq_concept.hpp"
#include "../constraints/linear-geq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

#include "builder.hpp"
#include "print_icn.hpp"

using namespace std;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|ll|lg|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -s NUMBER_SAMPLINGS [-p PARAMETERS] [-l] [--xp]\n"
	     << "   OR: " << argv[0] << " -c {ad|le|ll|lg|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -i INPUT_FILE -ci COMPLETE_INPUT_FILE [-p PARAMETERS] [--xp]\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-c, --constraint {ad|le|ll|lg|lt|ol|cm}, respectively for AllDiff, Linear equation, Linear inequation <=, Linear inequation >=, Less than, Overlap 1D and Connection minimum.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint.\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN, the maximal value variables can take.\n"
	     << "-s, --sampling NUMBER_SAMPLINGS, the number of required solutions and non-solutions.\n"
	     << "-i, --input INPUT_FILE containing sampled configurations.\n"
	     << "-ci, --complete_input COMPLETE_INPUT_FILE containing the full configuration space.\n"
	     << "-p, --params PARAMETERS, the list of parameters required.\n"
	     << "-l, --latin for performing Latin Hypercube samplings instead of Monte Carlo samplings.\n"
	     << "--xp to print on the screen results for experiments only.\n"
	     << "--long to search for 1 minute instead of 100ms.\n"
	     << "--debug.\n";
}

int main( int argc, char **argv )
{
	string constraint;
	int nb_vars, max_value;
	int samplings;
	bool do_samplings = false;
	int training_size;
	bool has_parameters;
	double params_value;
	vector<double> params;
	bool xp;
	bool debug;
	bool long_run;
	bool hyperparameters_tuning;
	bool latin_sampling;
	string input_file_path;
	string line, string_number;
	ifstream input_file;
	ifstream input_costs_file;

	map<string, pair<double,double>> cost_map;
	vector<int> random_solutions;
	vector<int> random_configurations;
	unique_ptr<Concept> concept_;

	auto start = std::chrono::steady_clock::now();
	int number_configurations_in_file = 0;
	
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-ci", "--complete_input", "-p", "--params", "--tournament", "--pop", "--steady", "--mingen", "--crossover", "--mutation", "--replacement", "--seed" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"d", "max_domain"} ) ) )
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
	cmdl( {"d", "max_domain"}, 9) >> max_value;
	cmdl( {"s", "sampling"}, 100) >> samplings;

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

	if( cmdl[ { "--long" } ] )
		long_run = true;
	else
		long_run = false;

	if( cmdl[ { "--paramILS" } ] )
		hyperparameters_tuning = true;
	else
		hyperparameters_tuning = false;

	if( !( cmdl( {"c", "constraint"} ) >> constraint )
	    ||
	    ( constraint.compare("ad") != 0
	      && constraint.compare("le") != 0
	      && constraint.compare("ll") != 0
	      && constraint.compare("lg") != 0
	      && constraint.compare("lt") != 0
	      && constraint.compare("ol") != 0
	      && constraint.compare("cm") != 0 ) )
	{
		cerr << "Must provide a valid constraint among ad, le, ll, lg, lt, ol and cm. You provided '" << cmdl( {"c", "constraint"} ).str() << "'\n";
		usage( argv );
		return EXIT_FAILURE;
	}
	else
	{
		if( constraint.compare("ad") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: AllDiff.\n";
			concept_ = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear equation.\n";
			concept_ = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("ll") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear inequation <=.\n";
			concept_ = make_unique<LinearLeqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("lg") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear inequation >=.\n";
			concept_ = make_unique<LinearGeqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("lt") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Less than.\n";
			concept_ = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Overlap 1D.\n";
			concept_ = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept_ = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}
	
	if( cmdl[ { "-l", "--latin" } ] )
		latin_sampling = true;
	else
		latin_sampling = false;
	
	if( cmdl( {"i", "input"} ) )
	{
		cmdl( {"i", "input"} ) >> input_file_path;

		if( !xp && !hyperparameters_tuning )
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
	else if( cmdl( {"ci", "complete_input"} ) )
	{
		cmdl( {"ci", "complete_input"} ) >> input_file_path;

		if( !xp && !hyperparameters_tuning )
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
	else
	{
		do_samplings = true;
		if( latin_sampling )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Perform Latin Hypercube sampling.\n";
			cap_draw( concept_, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
		else
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Perform Monte Carlo sampling.\n";
			cap_draw_monte_carlo( concept_, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
	}

	if( cmdl( {"i", "input"} ) || cmdl( {"ci", "complete_input"} ) )
	{
		double manhattan_cost;
		std::string input_costs_file_path = input_file_path.substr( 0, input_file_path.length() - 4 ) + std::string("_costs.txt");

		input_costs_file.open( input_costs_file_path );
		while( getline( input_costs_file, line ) )
		{
			auto delimiter = line.find(" ");
			std::string solution_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 1 );
			delimiter = line.find(" ");
			std::string hamming_cost = line.substr( 0, delimiter );
			line.erase(0, delimiter + 1 );
			stringstream line_stream( line );
			line_stream >> manhattan_cost;
			cost_map.emplace( solution_token, std::pair<double,double>( std::stod( hamming_cost ), manhattan_cost ) );
		}
		
		input_costs_file.close();
	}
	else
		cost_map = compute_metric_hamming_and_manhattan( random_solutions, random_configurations, nb_vars );

	training_size = number_configurations_in_file == 0 ? samplings*2 : number_configurations_in_file;	

	if( !xp && !hyperparameters_tuning )
	{
		cout << "Number of variables: " << nb_vars
		     << "\nMax domain value: " << max_value;

		cout << "\nTotal number of training configurations: " << training_size;
		if( do_samplings )
			cout << " (sampled)";
		cout << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
		     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n";
	}

	Builder builder( cost_map, random_solutions, random_configurations, has_parameters, nb_vars, max_value, params );

  ghost::Solver solver( builder );
  ghost::Options options;
  options.parallel_runs = true;
  options.print = std::make_shared<PrintICN>();
  
  double error = 0.;
  std::vector<int> solution;

  bool successful_run;
  
  if( long_run )
	  successful_run = solver.solve( error, solution, 30s, options );
  else
	  successful_run = solver.solve( error, solution, 200ms, options );

  int fitness_integer = static_cast<int>( floor( error ) );
  double regularization_term = error - fitness_integer;
  
	if( xp )
	{
		if( successful_run )
			cout << "1 ";
		else
			cout << "0 ";		    
		cout << static_cast<double>( fitness_integer ) / training_size << " ";
		for( auto val : solution )
			cout << val;
		cout << "\n";
	}
	else
	{
		if( successful_run )
			cout << "SUCCESS\n";
		else
			cout << "FAILURE\n";		    

		if( hyperparameters_tuning )
		{
			auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>( std::chrono::steady_clock::now() - start ).count();
			
			cout << "final quality is " << static_cast<double>( fitness_integer ) / training_size << "\n"
			     << "runtime is " << elapsed_time << "\n";
		}
		else
		{
			cout << "Fitness on the whole training set: " << fitness_integer
			     << "\nRegularization term: " << regularization_term
			     << "\nMean fitness: " << static_cast<double>( fitness_integer ) / training_size
			     << "\nHas parameters: " << std::boolalpha << has_parameters
			     << "\nNumber of variables: " << nb_vars
			     << "\nMax domain value: " << max_value
			     << "\nNumber of training configurations: " << training_size;
			if( do_samplings )
				cout << " (sampled)";
			
			cout << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
			     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n\nFunction: ";
			for( auto val : solution )
				cout << val;
			cout << "\n\nModel:\n";
			print_model( solution );
		}
	}
  
  return EXIT_SUCCESS;
}
