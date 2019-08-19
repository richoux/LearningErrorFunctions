#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <string>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>
#include <ghost/objective.hpp>
#include <ghost/solver.hpp>

#include "ctr.hpp"
#include "obj_ecl.hpp"

using namespace std;
using namespace ghost;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE RANDOM_WALK_LENGTH\n";
}

int main( int argc, char **argv )
{
	if( argc != 4 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below
	int max_value = stoi( argv[2] );
	int random_walk_length = stoi( argv[3] );

	int nb_coeff = nb_vars * 10;
	vector< Variable > coefficients; // be careful: variables of our problem actually represent coefficients
	for( int i = 0; i < nb_coeff; ++i )
		coefficients.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, max_value + 1 );

	// Idea: we could have a larger domain and take into account coeff_value / 10 to have finer-grain and non integer coefficients.
		
	vector< reference_wrapper< Variable > > coeff_ref( coefficients.begin(), coefficients.end() );


	shared_ptr< Constraint > ctr = make_shared< Ctr >( coeff_ref );
	vector< shared_ptr< Constraint >> constraints { ctr };
	
	shared_ptr< Objective > objective = make_shared< Obj_ECL >( random_walk_length, nb_vars, max_value );
	
	Solver solver( coefficients, constraints, objective );
	
	double cost = 0.;
	vector<int> solution( coeff_ref.size(), 0 );

	solver.solve( cost, solution, 1000000, 10000000 );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
