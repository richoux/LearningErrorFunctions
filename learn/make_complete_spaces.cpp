#include <vector>
#include <string>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <iterator>

// Command line option management
#include <argh.h>

#include "../utils/increment.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

using namespace std;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -o OUTPUT_FILE [-p PARAMETERS]\n"
	     << "Arguments:\n"
	     << "-h, --help\n"
	     << "-c, --constraint {ad|le|lt|ol|cm}\n"
	     << "-n, --nb_vars NB_VARIABLES\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN\n"
	     << "-o, --output OUTPUT_FILE\n"
	     << "-p, --params PARAMETERS\n";
}

int main( int argc, char** argv )
{
	string constraint;
	int nb_vars, max_value;
	unique_ptr<Concept> concept_;
	vector<double> params;
	double params_value;
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
			concept_ = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			cout << "Constraint: Linear equation.\n";
			concept_ = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}
		
		if( constraint.compare("lt") == 0 )
		{
			cout << "Constraint: Less than.\n";
			concept_ = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			cout << "Constraint: Overlap 1D.\n";
			concept_ = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept_ = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}

	output_file.open( output_file_path );

	vector<int> configurations( nb_vars, 1 );
	do
	{
		output_file << concept_->concept_( configurations ) << " : ";
		
		std::copy( configurations.begin(),
		           configurations.end(),
		           ostream_iterator<int>( output_file, " " ) );
		
		output_file << "\n";
		increment( configurations, max_value );
	} while( std::any_of( configurations.begin(), configurations.end(), [&max_value](auto& c){ return c != max_value; } ) );

	// last round
	output_file << concept_->concept_( configurations ) << " : ";
	
	std::copy( configurations.begin(),
	           configurations.end(),
	           ostream_iterator<int>( output_file, " " ) );
	
	output_file << "\n";
	output_file.close();

	return EXIT_SUCCESS;
}
