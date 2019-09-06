#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

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

	// Proper way to initialize a Mersenne Twister
	array<int, mt19937::state_size> seed_data;
	random_device r;
	generate_n( seed_data.data(), seed_data.size(), std::ref( r ) );
	seed_seq seq( seed_data.begin(), seed_data.end() );
	mt19937 gen( seq );
	// To have a random initialization of coefficients in [-1, 1]
	uniform_int_distribution<> initialization( 40, 60 );
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 0 to max_value 
	int max_value = stoi( argv[2] );

	int random_walk_length = stoi( argv[3] );

	int nb_coeff = nb_vars * 10;
	vector< Variable > coefficients; // be careful: variables of our problem actually represent coefficients

	// coefficients can take values from -5 to 5, with strides of 0.1.
	for( int i = 0; i < nb_coeff; ++i )
		coefficients.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 100 );

	// all coefficients fixed at 1
	for( auto& c : coefficients )
		c.set_value( initialization( gen ) );
	
	// Idea: we could have a larger domain and take into account coeff_value / 10 to have finer-grain and non integer coefficients.

	vector< reference_wrapper< Variable > > coeff_ref( coefficients.begin(), coefficients.end() );
		
	auto it_middle = coefficients.begin() + nb_coeff/2;
	vector< reference_wrapper< Variable > > coeff_first_half( coefficients.begin(), it_middle );
	vector< reference_wrapper< Variable > > coeff_second_half( it_middle, coefficients.end() );
	
	vector< reference_wrapper< Variable > > coeff_2_by_2_1( coefficients.begin(), coefficients.end() );
	vector< reference_wrapper< Variable > > coeff_2_by_2_2( coefficients.begin(), coefficients.end() );
	vector< reference_wrapper< Variable > > coeff_1_by_1_1( coefficients.begin(), coefficients.end() );
	vector< reference_wrapper< Variable > > coeff_1_by_1_2( coefficients.begin(), coefficients.end() );
	
	for( int i = nb_coeff - 1; i >= 0; --i )
	{
		if( i % 2 == 0 )
			coeff_1_by_1_2.erase( coeff_1_by_1_2.begin() + i );
		else
			coeff_1_by_1_1.erase( coeff_1_by_1_1.begin() + i );

		if( i % 4 < 2 )
			coeff_2_by_2_2.erase( coeff_2_by_2_2.begin() + i );
		else
			coeff_2_by_2_1.erase( coeff_2_by_2_1.begin() + i );			
	}

	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr >( coeff_ref, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_first_half = make_shared< Ctr >( coeff_first_half, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_second_half = make_shared< Ctr >( coeff_second_half, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_2_2_1 = make_shared< Ctr >( coeff_2_by_2_1, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_2_2_2 = make_shared< Ctr >( coeff_2_by_2_2, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_1_1_1 = make_shared< Ctr >( coeff_1_by_1_1, nb_vars, max_value, gen );
	shared_ptr< Constraint > ctr_1_1_2 = make_shared< Ctr >( coeff_1_by_1_2, nb_vars, max_value, gen );
	vector< shared_ptr< Constraint >> constraints { ctr_all_var, ctr_first_half, ctr_second_half, ctr_2_2_1, ctr_2_2_2, ctr_1_1_1, ctr_1_1_2 };
	
	shared_ptr< Objective > objective = make_shared< Obj_ECL >( random_walk_length, nb_vars, max_value );
	
	Solver solver( coefficients, constraints, objective );
	
	double cost = 0.;
	vector<int> solution( coeff_ref.size(), 0 );

	solver.solve( cost, solution, 10000000, 100000000, true );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
