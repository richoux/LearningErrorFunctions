#include <vector>
#include <iostream>
#include <string>

#include "../utils/random_draw.hpp"
#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"

#include "../utils/randutils.hpp"

using namespace std;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE [PERCENT]\n";
}

int main( int argc, char **argv )
{
	if( argc < 3 || argc > 4 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	// Proper way to initialize a Mersenne Twister
	// array<int, mt19937::state_size> seed_data;
	// random_device r;
	// generate_n( seed_data.data(), seed_data.size(), std::ref( r ) );
	// seed_seq seq( seed_data.begin(), seed_data.end() );
	// mt19937 gen( seq );
	// // To have a random initialization of coefficients in [-1, 1]
	// uniform_int_distribution<> initialization( 40, 60 );

	// randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 0 to max_value 
	int max_value = stoi( argv[2] );

	double percent;
	if( argc == 4 )
		percent = stod( argv[3] );
	else
		percent = 1.;

	unique_ptr<Concept> concept = make_unique<AllDiffConcept>( nb_vars, max_value );
	
	vector<int> solutions;
	vector<int> not_solutions;
	//random_draw( concept, nb_vars, max_value, solutions, not_solutions, percent );
	random_draw_monte_carlo( concept, nb_vars, max_value, solutions, not_solutions, percent );

	int sampling_size = (int)( solutions.size() + not_solutions.size() );

	cout << "Percent of search space sampled: " << percent << "\n";
	//monte carlo
	cout << "Density of solutions: " << ( static_cast<double>( solutions.size() ) * 100 ) / sampling_size << "%\n (" << solutions.size() << " over " << sampling_size << " samples)\n";
	//latin
	//cout << "Density of solutions: " << ( static_cast<double>( solutions.size() ) * 100 ) / sampling_size << "%\n (" << solutions.size() / nb_vars << " over " << sampling_size / nb_vars << " samples)\n";
}
