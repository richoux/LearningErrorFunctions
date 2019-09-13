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

#if defined SMOOTH_CTR
// Constraints aiming for smooth function, so objective function aiming for max function outputs
#include "ctr_smooth.hpp"
#include "obj_max_outputs.hpp"
#else
// Constraints aiming for max function outputs, so objective function aiming for smooth function
#include "ctr_high_outputs.hpp"
#include "obj_ecl.hpp"
#endif

#include "random_draw.hpp"

#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE\n";
}

int main( int argc, char **argv )
{
	if( argc != 3 )
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

	randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 0 to max_value 
	int max_value = stoi( argv[2] );

#if not defined SMOOTH_CTR
	vector< vector<int> > random_solutions;
	random_draw( nb_vars, max_value, random_solutions, vector< vector<int> >() );
#endif
	
	int nb_coeff = nb_vars * 10;
	vector< Variable > coefficients; // be careful: variables of our problem actually represent coefficients

	// coefficients can take values from -5 to 5, with strides of 0.1.
	for( int i = 0; i < nb_coeff; ++i )
		coefficients.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 100 );

	// all coefficients fixed at 1
	for( auto& c : coefficients )
		c.set_value( rng.uniform( 40, 60 ) );
	
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

#if defined SMOOTH_CTR
	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_smooth >( coeff_ref, nb_vars, max_value );
	shared_ptr< Constraint > ctr_first_half = make_shared< Ctr_smooth >( coeff_first_half, nb_vars, max_value );
	shared_ptr< Constraint > ctr_second_half = make_shared< Ctr_smooth >( coeff_second_half, nb_vars, max_value );
	shared_ptr< Constraint > ctr_2_2_1 = make_shared< Ctr_smooth >( coeff_2_by_2_1, nb_vars, max_value );
	shared_ptr< Constraint > ctr_2_2_2 = make_shared< Ctr_smooth >( coeff_2_by_2_2, nb_vars, max_value );
	shared_ptr< Constraint > ctr_1_1_1 = make_shared< Ctr_smooth >( coeff_1_by_1_1, nb_vars, max_value );
	shared_ptr< Constraint > ctr_1_1_2 = make_shared< Ctr_smooth >( coeff_1_by_1_2, nb_vars, max_value );
#else
	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_HO >( coeff_ref, nb_vars, max_value );
	shared_ptr< Constraint > ctr_first_half = make_shared< Ctr_HO >( coeff_first_half, nb_vars, max_value );
	shared_ptr< Constraint > ctr_second_half = make_shared< Ctr_HO >( coeff_second_half, nb_vars, max_value );
	shared_ptr< Constraint > ctr_2_2_1 = make_shared< Ctr_HO >( coeff_2_by_2_1, nb_vars, max_value );
	shared_ptr< Constraint > ctr_2_2_2 = make_shared< Ctr_HO >( coeff_2_by_2_2, nb_vars, max_value );
	shared_ptr< Constraint > ctr_1_1_1 = make_shared< Ctr_HO >( coeff_1_by_1_1, nb_vars, max_value );
	shared_ptr< Constraint > ctr_1_1_2 = make_shared< Ctr_HO >( coeff_1_by_1_2, nb_vars, max_value );
#endif
	
	vector< shared_ptr< Constraint >> constraints { ctr_all_var, ctr_first_half, ctr_second_half, ctr_2_2_1, ctr_2_2_2, ctr_1_1_1, ctr_1_1_2 };
	
#if defined SMOOTH_CTR
	shared_ptr< Objective > objective = make_shared< Obj_MO >( nb_vars, max_value );
#else
	shared_ptr< Objective > objective = make_shared< Obj_ECL >( nb_vars, max_value, random_solutions );
#endif

	Solver solver( coefficients, constraints, objective );
	
	double cost = 0.;
	vector<int> solution( coeff_ref.size(), 0 );

	solver.solve( cost, solution, 10000, 100000, true );
	//solver.solve( cost, solution, 10000000, 1000000000, true );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
