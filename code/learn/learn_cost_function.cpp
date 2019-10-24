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

#include "ctr_high_outputs.hpp"
#include "obj_ecl.hpp"

#include "ctr_dependency.hpp"
#include "ctr_active_unit.hpp"

#include "random_draw.hpp"

#include "../utils/randutils.hpp"
#include "../utils/convert.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"

using namespace std;
using namespace ghost;

constexpr	int number_layers = 2;

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

	randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 0 to max_value 
	//int max_value = stoi( argv[2] );
	int max_value = nb_vars - 1;
		
	vector<int> random_solutions;
	vector<int> random_configurations;

	unique_ptr<Concept> concept;
#if defined AD
	concept = make_unique<AllDiffConcept>( nb_vars, max_value );
#elif defined LE
	concept = make_unique<LinearEqConcept>( nb_vars, max_value );
#elif defined LT
	concept = make_unique<LessThanConcept>( nb_vars, max_value );	
#endif
	
	if( argc == 3 )
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, stod( argv[2] ) );
	else
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations );
	
	vector<int> few_configurations( random_configurations.begin(), random_configurations.begin() + random_solutions.size() );
	auto cost_map = compute_metric( random_solutions, few_configurations, nb_vars, max_value );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";
	
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

	shared_ptr< Constraint > ctr_all_var = make_shared< Ctr_HO >( weights_ref, nb_vars, few_configurations, cost_map );

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
	
	shared_ptr< Objective > objective = make_shared< Obj_ECL >( std::move( concept ), nb_vars, random_solutions, few_configurations );

	Solver solver( weights, constraints, objective );
	
	double cost = 0.;
	vector<int> solution( weights_ref.size(), 0 );

	solver.solve( cost, solution, 1000000, 10000000 );
	// 60000000 ms = 1m
	//solver.solve( cost, solution, 10000000, 60000000 );
	// 3600000000 microseconds = 1h
	//solver.solve( cost, solution, 100000000, 3600000000 );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
}
