#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

#include <iostream>
#include <fstream>
#include <iterator>
#include <chrono>

// Command line option management
#include <argh.h>

#include "../utils/random_draw.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

using namespace std;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -s SAMPLING_PRECISION -o OUTPUT_FILE [-p PARAMETERS] [-l]\n"
	     << "Arguments:\n"
	     << "-h, --help\n"
	     << "-c, --constraint {ad|le|lt|ol|cm}\n"
	     << "-n, --nb_vars NB_VARIABLES\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN\n"
	     << "-s, --sampling NUMBER_SAMPLING\n"
	     << "-o, --output OUTPUT_FILE\n"
	     << "-p, --params PARAMETERS\n"
	     << "-l, --latin\n";
}

int main( int argc, char** argv )
{
	chrono::duration<double,milli> elapsedTime(0);
	chrono::time_point<chrono::steady_clock> start;
	start = chrono::steady_clock::now();
	
	string constraint;
	int nb_vars, max_value;
	int samplings;
	vector<int> random_solutions;
	vector<int> random_configurations;
	unique_ptr<Concept> concept;
	map<string, double> cost_map;
	vector<double> params;
	double params_value;
	bool latin_sampling;
	string output_file_path;
	ofstream output_file;
	
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-p", "--params", "-o", "--output", } );
	// argh::parser cmdl;
	// cmdl.add_param( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-p", "--params" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"d", "max_domain"} ) && cmdl( {"o", "output"} ) ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	cmdl( {"n", "nb_vars"}, 9) >> nb_vars;
	cmdl( {"d", "max_domain"}, 9) >> max_value;
	cmdl( {"o", "output"} ) >> output_file_path;	
	cmdl( {"s", "sampling"}, 100) >> samplings;

	cmdl( {"p", "params"}, 1.0 ) >> params_value;
	params = vector<double>( nb_vars, params_value );

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
			concept = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			cout << "Constraint: Linear equation.\n";
			concept = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}
		
		if( constraint.compare("lt") == 0 )
		{
			cout << "Constraint: Less than.\n";
			concept = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			cout << "Constraint: Overlap 1D.\n";
			concept = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}

	cout << nb_vars << "-" << max_value;	
	if( constraint.compare("le") == 0 || constraint.compare("ol") == 0 || constraint.compare("cm") == 0 )
		cout << "-" << params_value;
	cout << "\n";

	
	if( cmdl[ { "-l", "--latin" } ] )
		latin_sampling = true;
	else
		latin_sampling = false;

	int number_draws;
	
	if( latin_sampling )
	{
		cout << "Perform Latin Hypercube sampling.\n";
		number_draws = cap_draw( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
	}
	else
	{
		cout << "Perform Monte Carlo sampling.\n";
		number_draws = cap_draw_monte_carlo( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
	}

	if( (int)random_solutions.size() == 0 )
	{
		cerr << "No solutions. Abort.\n";
		return EXIT_FAILURE;
	}
	
	unsigned long long int space_size = static_cast<unsigned long long int>( std::pow( max_value, nb_vars ) );
	
	output_file.open( output_file_path );
	output_file << (int)random_solutions.size() / nb_vars << "\n";

	for( int i = 0; i < (int)random_solutions.size(); i += nb_vars )
	{
		std::copy( random_solutions.begin() + i,
		           random_solutions.begin() + i + nb_vars,
		           ostream_iterator<int>( output_file, " " ) );

		output_file << "\n";
	}
	
	for( int i = 0; i < (int)random_configurations.size(); i += nb_vars )
	{
		std::copy( random_configurations.begin() + i,
		           random_configurations.begin() + i + nb_vars,
		           ostream_iterator<int>( output_file, " " ) );

		output_file << "\n";
	}

	output_file.close();

	cout << "Number of solutions: " << samplings << "\n";
	cout << "Space size: " << space_size << "\n";

	cout << "Percent solutions: " << ( static_cast<double>( samplings ) * 100 ) / number_draws << "\n";
	cout << "Percent explored space: " << ( static_cast<double>( samplings ) * 200 ) / space_size << "\n";

	elapsedTime = chrono::steady_clock::now() - start;
	cout << "Elapsed time: " << elapsedTime.count() << "ms\n";
	return EXIT_SUCCESS;
}
