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

#include "ctr_no_empty_network.hpp"
#include "ctr_unique_agreg_function.hpp"
#include "obj_hamming.hpp"

#include "function_to_learn_cppn.hpp" // for number_functions

#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"
#include "../utils/random_draw.hpp"

#include "../constraints/concept.hpp"
#if defined AD
#include "../constraints/all-diff_concept.hpp"
#elif defined LE
#include "../constraints/linear-eq_concept.hpp"
#elif defined LT
#include "../constraints/less-then_concept.hpp"
#endif

using namespace std;
using namespace ghost;

constexpr	int number_layers = 2;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE PRECISION [Param1] [Param2]\n";
}

//////////////////////////////////

int main( int argc, char **argv )
{
	if( argc < 4 || argc > 6 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}
	
	randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // not the size the vector<Variable>, see below

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 1 to max_value included
	int max_value = stoi( argv[2] );

	double precision = stod( argv[3] );
	
	int param_1{1}, param_2{0}; 

	if( argc > 4 )
	{
		param_1 = stoi( argv[4] );
		if( argc == 6 )
			param_2 = stoi( argv[5] );
	}
	
	vector<int> random_solutions;
	vector<int> random_configurations;

	int number_units_compar = number_units_compar_1_param;
	
	unique_ptr<Concept> concept;
#if defined AD
	concept = make_unique<AllDiffConcept>( nb_vars, max_value );
#elif defined LE
	// argv[3] is the right-hand side value of the equation
	concept = make_unique<LinearEqConcept>( nb_vars, max_value, param_1 );
#elif defined LT
	concept = make_unique<LessThanConcept>( nb_vars, max_value );	
#endif
	
	random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, precision );
	
	vector<int> few_configurations( random_configurations.begin(),
	                                random_configurations.begin() + random_solutions.size() );
	
	auto cost_map = compute_metric_hamming_only( random_solutions, few_configurations, nb_vars );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";
	
	/*************/
	/* Variables */
	/*************/
	vector< Variable > weights; // be careful: variables of our problem actually represent weights
	for( int i = 0; i < number_units_transfo * number_units_compar + number_agregation_functions; ++i )
		weights.emplace_back( std::string("v") + std::to_string(i),
		                      std::string("v") + std::to_string(i),
		                      0,
		                      2 );

	vector< reference_wrapper< Variable > > weights_ref( weights.begin(), weights.end() );
	vector< reference_wrapper< Variable > > weights_network( weights_ref.begin(), std::prev( weights_ref.end(), number_agregation_functions ) );
	vector< reference_wrapper< Variable > > weights_agregation( std::prev( weights_ref.end(), number_agregation_functions ), weights_ref.end() );	
	

	/***************/
	/* Constraints */
	/***************/
	shared_ptr< Constraint > ctr_no_empty_network	= make_shared< Ctr_no_empty_network >( weights_network );
	shared_ptr< Constraint > ctr_unique_agreg_function	= make_shared< Ctr_unique_agreg_function >( weights_agregation );
	vector< shared_ptr< Constraint >> constraints { ctr_no_empty_network, ctr_unique_agreg_function };

	/**********************/
	/* Objective function */
	/**********************/
	shared_ptr< Objective > objective = make_shared< Obj_hamming >( std::move( concept ),
	                                                                nb_vars,
	                                                                std::max(1, argc - 4),
	                                                                param_1,
	                                                                param_2,
	                                                                random_solutions,
	                                                                few_configurations,
	                                                                cost_map );


	double cost = 0.;

	/*
	// TESTS
	vector<int> vec{0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0};
	for( int i = 0; i < (int)vec.size(); ++i )
		if( vec[i] == 1 )
			weights[i].set_value( 1 );

	cost = objective->cost( weights );
	cout << "\nCost: " <<  cost << "\n";
  
  /*/

	Solver solver( weights, constraints, objective );
	
	vector<int> solution( weights_ref.size(), 0 );

	//solver.solve( cost, solution, 100000, 1000000 );
	//solver.solve( cost, solution, 1000000, 10000000 );
	// 60000000 ms = 1m
	solver.solve( cost, solution, 1000000, 60000000 );
	// 3600000000 microseconds = 1h
	//solver.solve( cost, solution, 100000000, 3600000000 );

	std::cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		std::cout << " " << v;
	std::cout << "\n";
  //*/
}
