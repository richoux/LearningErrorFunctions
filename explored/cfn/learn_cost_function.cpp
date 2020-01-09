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

#include "ctr_dependency.hpp"
#include "ctr_active_unit.hpp"

#include "random_draw.hpp"

#include "../utils/randutils.hpp"
#include "../utils/convert.hpp"

using namespace std;
using namespace ghost;

double hamming_manhattan_metric( const vector<int>& configuration,
                                 const vector<int>& solution,
                                 int start_config,
                                 int start_sol,
                                 int nb_vars,
                                 int max_value )
{
	double cost = 0.;
	double diff = 0.;

	int max_diff = nb_vars * max_value;
	
	for( int i = 0; i < nb_vars; ++i )
		if( configuration[ start_config + i ] != solution[ start_sol + i ] )
		{
			cost += 1;
			diff += std::abs( solution[ start_sol + i ] - configuration[ start_config + i ] );
		}

	// normalization
	diff = 0.9 * ( diff / max_diff );

	//cost += ( diff / ( std::pow( 10, std::floor( std::log10( diff ) ) + 1 ) ) );
	return cost + diff;
}

map<string, double> compute_metric( const vector<int>& random_solutions,
                                    const vector<int>& random_configurations,
                                    int nb_vars,
                                    int max_value )
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
			cost = hamming_manhattan_metric( random_configurations, random_solutions, c, s, nb_vars, max_value );
			if( cost < min_cost )
				min_cost = cost;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ] = min_cost;
	}

	return costs;
}

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
	if( argc == 4 )
		random_draw( nb_vars, max_value, random_solutions, random_configurations, stod( argv[3] ) );
	else
		random_draw( nb_vars, max_value, random_solutions, random_configurations );
	
	vector<int> few_configurations( random_configurations.begin(), random_configurations.begin() + random_solutions.size() );
	auto cost_map = compute_metric( random_solutions, few_configurations, nb_vars, max_value );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";
#endif

	int number_layers = 2;
	
	vector< Variable > weights; // be careful: variables of our problem actually represent weights
	for( int i = 0; i < 7 * number_layers; ++i )
		weights.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 2 );

	vector< reference_wrapper< Variable > > weights_ref( weights.begin(), weights.end() );
	vector< reference_wrapper< Variable > > dependency_id ( weights_ref.begin(), weights_ref.begin() + 8 );
	vector< reference_wrapper< Variable > > dependency_abs ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_abs.push_back( weights_ref[8] );

	vector< reference_wrapper< Variable > > dependency_sin ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_sin.push_back( weights_ref[9] );

	vector< reference_wrapper< Variable > > dependency_tanh ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_tanh.push_back( weights_ref[10] );

	vector< reference_wrapper< Variable > > dependency_cubic_tanh ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_cubic_tanh.push_back( weights_ref[11] );

	vector< reference_wrapper< Variable > > dependency_sigmoid ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_sigmoid.push_back( weights_ref[12] );

	vector< reference_wrapper< Variable > > dependency_gaussian ( weights_ref.begin(), weights_ref.begin() + 7 );
	dependency_gaussian.push_back( weights_ref[13] );

	vector< reference_wrapper< Variable > > last_layer_active_unit ( weights_ref.begin() + 7, weights_ref.end() );

#if defined SMOOTH_CTR
	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_smooth >( weights_ref, nb_vars, max_value );
#else
	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_HO >( weights_ref, nb_vars, few_configurations, cost_map );
#endif

	shared_ptr< Constraint > ctr_dependency_id = make_shared< Ctr_dependency >( dependency_id );
	shared_ptr< Constraint > ctr_dependency_abs = make_shared< Ctr_dependency >( dependency_abs );
	shared_ptr< Constraint > ctr_dependency_sin = make_shared< Ctr_dependency >( dependency_sin );
	shared_ptr< Constraint > ctr_dependency_tanh = make_shared< Ctr_dependency >( dependency_tanh );
	shared_ptr< Constraint > ctr_dependency_cubic_tanh = make_shared< Ctr_dependency >( dependency_cubic_tanh );
	shared_ptr< Constraint > ctr_dependency_sigmoid = make_shared< Ctr_dependency >( dependency_sigmoid );
	shared_ptr< Constraint > ctr_dependency_gaussian = make_shared< Ctr_dependency >( dependency_gaussian );	

	shared_ptr< Constraint > ctr_last_layer_active_unit = make_shared< Ctr_active_unit >( last_layer_active_unit );

	vector< shared_ptr< Constraint >> constraints { ctr_all_var,
	                                                ctr_dependency_id,
	                                                ctr_dependency_sin,
	                                                ctr_dependency_tanh,
	                                                ctr_dependency_cubic_tanh,
	                                                ctr_dependency_sigmoid,
	                                                ctr_dependency_gaussian,
	                                                ctr_last_layer_active_unit };	                                                
	
#if defined SMOOTH_CTR
	shared_ptr< Objective > objective = make_shared< Obj_MO >( nb_vars, max_value );
#else
	shared_ptr< Objective > objective = make_shared< Obj_ECL >( nb_vars, random_solutions, few_configurations );
#endif

	Solver solver( weights, constraints, objective );
	
	double cost = 0.;
	vector<int> solution( weights_ref.size(), 0 );

	solver.solve( cost, solution, 10000000, 10000000 );
	// 60000000 ms = 1m
	//solver.solve( cost, solution, 10000000, 60000000 );
	// 3600000000 microseconds = 1h
	//solver.solve( cost, solution, 100000000, 3600000000 );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
