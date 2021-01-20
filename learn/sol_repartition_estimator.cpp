// To create repart fils into the space folder

#include <vector>
#include <string>

#include <iostream>

// Command line option management
#include <argh.h>

#include "../utils/random_draw.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

#include "../utils/randutils.hpp"

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
	     << "-p, --params PARAMETERS\n";
}

int main( int argc, char** argv )
{
	string constraint;
	int nb_vars, max_value;
	int samplings;
	int nb_solutions;
	unique_ptr<Concept> concept;
	vector<double> params;
	double params_value;

	randutils::mt19937_rng rng;
	
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-p", "--params" } );
	// argh::parser cmdl;
	// cmdl.add_param( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-p", "--params" } );
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

	cmdl( {"n", "nb_vars"}, 9) >> nb_vars;
	cmdl( {"d", "max_domain"}, 9) >> max_value;
	cmdl( {"s", "sampling"}, 10000000) >> samplings;

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

	vector<int> sample( nb_vars );
	nb_solutions = 0;
	
	for( int s = 0; s < samplings; ++s )
	{
		rng.generate( sample, 1, max_value );
		if( concept->concept( sample ) )
			++nb_solutions;
	}
	
	if( nb_solutions == 0 )
	{
		cerr << "No solutions. Abort.\n";
		return EXIT_FAILURE;
	}

	cout << "Number of solutions: " << nb_solutions << "\n";
	cout << "Number of samplings: " << samplings << "\n";
	cout << "Estimated percent solutions: " << ( static_cast<double>( nb_solutions ) * 100 ) / samplings << "\n";

	return EXIT_SUCCESS;
}
