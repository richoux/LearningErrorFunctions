#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <map>

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
#include "../utils/convert.hpp"

using namespace std;
using namespace ghost;

double hamming_manhattan_metric( const vector<int>& configuration,
                                 const vector<int>& solution,
                                 int start_config,
                                 int start_sol,
                                 int nb_vars )
{
	double cost = 0.;

	for( int i = 0; i < nb_vars; ++i )
		if( configuration[ start_config + i ] != solution[ start_sol + i ] )
		{
			double diff = std::abs( solution[ start_sol + i ] - configuration[ start_config + i ] );
			cost += 1 + ( diff / ( std::pow( 10, std::floor( std::log10( diff ) ) + 1 ) ) );
		}

	return cost;
}
// double hamming_manhattan_metric( const vector<int>& configuration,
//                                  const vector<int>& solution,
//                                  int nb_vars )
// {
// 	double cost = 0.;

// 	for( int i = 0; i < nb_vars; ++i )
// 		if( configuration[i] != solution[i] )
// 		{
// 			double diff = std::abs( solution[i] - configuration[i] );
// 			cost += 1 + ( diff / ( std::pow( 10, std::floor( std::log10( diff ) ) + 1 ) ) );
// 		}

// 	return cost;
// }

map<string, double> compute_metric( const vector<int>& random_solutions,
                                    const vector<int>& random_configurations,
                                    int nb_vars )
{
	map<string, double> costs;

	for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		costs[ convert( random_solutions, s, s + nb_vars ) ] = 0.;
	
	for( int c = 0; c < (int)random_configurations.size(); c += nb_vars )
	{
		double cost;
		double min_cost = std::numeric_limits<double>::max();
				
		for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		{
			cost = hamming_manhattan_metric( random_configurations, random_solutions, c, s, nb_vars );
			if( cost < min_cost )
				min_cost = cost;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ] = min_cost;		
	}

	return costs;
}
// map<string, double> compute_metric( const vector< vector<int> >& random_solutions,
//                                     const vector< vector<int> >& random_configurations,
//                                     int nb_vars )
// {
// 	map<string, double> costs;

// 	for( auto& s : random_solutions )
// 		costs[ convert( s ) ] = 0.;
	
// 	for( auto& c : random_configurations )
// 	{
// 		double cost;
// 		double min_cost = std::numeric_limits<double>::max();
				
// 		for( auto& s : random_solutions )
// 		{
// 			cost = hamming_manhattan_metric( c, s, nb_vars );
// 			if( cost < min_cost )
// 				min_cost = cost;
// 		}

// 		costs[ convert( c ) ] = min_cost;		
// 	}

// 	return costs;
// }

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE\n";
}

//////////////////////////////////

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

	randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 0 to max_value 
	int max_value = stoi( argv[2] );

#if not defined SMOOTH_CTR
	vector<int> random_solutions;
	vector<int> random_configurations;
	// vector< vector<int> > random_solutions;
	// vector< vector<int> > random_configurations;
	if( argc == 4 )
		random_draw( nb_vars, max_value, random_solutions, random_configurations, stod( argv[3] ) );
	else
		random_draw( nb_vars, max_value, random_solutions, random_configurations );
	
	vector<int> few_configurations( random_configurations.begin(), random_configurations.begin() + random_solutions.size() );
	//vector< vector<int> > few_configurations( random_configurations.begin(), random_configurations.begin() + random_solutions.size() );
	auto cost_map = compute_metric( random_solutions, few_configurations, nb_vars );
#if defined CHRONO
	cout << "number of solutions: " << random_solutions.size() << "\n"
	     << "cost_map size: " << cost_map.size() << "\n";
#endif	
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
	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_HO >( coeff_ref, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_first_half = make_shared< Ctr_HO >( coeff_first_half, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_second_half = make_shared< Ctr_HO >( coeff_second_half, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_2_2_1 = make_shared< Ctr_HO >( coeff_2_by_2_1, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_2_2_2 = make_shared< Ctr_HO >( coeff_2_by_2_2, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_1_1_1 = make_shared< Ctr_HO >( coeff_1_by_1_1, nb_vars, max_value, random_solutions, cost_map );
	shared_ptr< Constraint > ctr_1_1_2 = make_shared< Ctr_HO >( coeff_1_by_1_2, nb_vars, max_value, random_solutions, cost_map );
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

	//solver.solve( cost, solution, 10000, 100000, true );
	solver.solve( cost, solution, 100000, 10000000, true );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
