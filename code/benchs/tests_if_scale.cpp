#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../utils/random_draw.hpp"
#include "../utils/metrics.hpp"
#include "../utils/convert.hpp"

#include "../constraints/concept.hpp"

#if defined AD
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/all-diff.hpp"
#elif defined LE
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/linear-eq.hpp"
#elif defined LT
#include "../constraints/less-then_concept.hpp"
#include "../constraints/less-then.hpp"
#endif

using namespace std;
using namespace ghost;

constexpr	int number_layers = 2;

void print_configuration( const vector<int>& vec, int start, int end )
{
	std::copy( vec.begin() + start, vec.begin() + end, std::ostream_iterator<int>( cout, " " ) );
	cout << "\n";
}

void change_values( vector<Variable>& vars, const vector<int>& vec, int start, int end )
{
	for( int i = 0; i < end - start; ++i )
		vars[i].set_value( vec[ start + i] );
}

void compare( vector<Variable>& vars, const vector<int>& vec, const unique_ptr<Constraint>& constraint, const map<string, double>& cost_map )
{
	int nb_vars = (int)vars.size();
	for( int i = 0; i < (int)vec.size(); i+=nb_vars )
	{
		print_configuration( vec, i, i + nb_vars );
		change_values( vars, vec, i, i + nb_vars );
		cout << "Estimated cost: " << constraint->cost() << "\n";
		cout << "Expected cost: " << cost_map.at( convert( vec, i, i + nb_vars ) ) << "\n\n";
	}
}

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE\n";
}

//////////////////////////////////

int main( int argc, char **argv )
{
#if defined LE
	if( argc < 3 || argc > 6 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}
#else
	if( argc < 3 || argc > 5 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}
#endif
	
	randutils::mt19937_rng rng;
	
	int nb_vars = stoi( argv[1] ); // number of variables

	// Again, we assume here that all variables share the same domain,
	// and that this domain contains all numbers from 1 to max_value included
	int max_value = stoi( argv[2] );
			
	vector<int> random_solutions;
	vector<int> random_configurations;

	unique_ptr<Concept> concept;
	unique_ptr<Constraint> constraint;
	
	// Create variables
  vector<Variable> variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 1, max_value );

  vector< reference_wrapper<Variable> > var_ref( variables.begin(), variables.end() );
	
#if defined AD
	concept = make_unique<AllDiffConcept>( nb_vars, max_value );
	constraint = make_unique< AllDiff >( var_ref );
#elif defined LE
	// argv[3] is the right-hand side value of the equation
	int rhs = stoi( argv[3] );
	concept = make_unique<LinearEqConcept>( nb_vars, max_value, rhs );
	constraint = make_unique< LinearEq >( var_ref, rhs );
#elif defined LT
	concept = make_unique<LessThanConcept>( nb_vars, max_value );	
	constraint = make_unique< LessThan >( var_ref );
#endif
	
#if defined LE
	if( argc == 5 )
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, stod( argv[4] ) );
	else
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations );
#else
	if( argc == 4 )
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, stod( argv[3] ) );
	else
		random_draw( concept, nb_vars, max_value, random_solutions, random_configurations );
#endif
	
	vector<int> few_configurations( random_configurations.begin(),
	                                random_configurations.begin() + random_solutions.size() );
	
	auto cost_map = compute_metric( random_solutions, few_configurations, nb_vars, max_value );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";

	// cout << "Compare with solutions\n";
	// compare( variables, random_solutions, constraint, cost_map );
	// cout << "\n\n"
	cout << "Compare with non-solutions\n";
	compare( variables, few_configurations, constraint, cost_map );

	return EXIT_SUCCESS;
}
	
