//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <strstream>  // ostrstream, istrstream

#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

// the general include for eo
#include <eo>
#include <ga.h>

// code from the CFN version
//-----------------------------------------------------------------------------
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

int nb_vars, max_value, nb_params, param_1{1}, param_2{0};
double precision;
vector<int> random_solutions;
vector<int> random_configurations;
int number_units_compar = number_units_compar_1_param;
unique_ptr<Concept> concept;
vector<int> few_configurations;
map<string, double> cost_map;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE PRECISION [Param1] [Param2]\n";
}

//-----------------------------------------------------------------------------
// define your individuals
typedef eoBit<double> Indi;        // A bitstring with fitness double
//-----------------------------------------------------------------------------

double fitness(const Indi& indi)
{
	set< pair<double, double> > costs;
	double cost = 0.0;
	vector<int> weights( indi.size(), 0 );
	for( int i = 0; i < (int)indi.size(); ++i )
		if( indi[i] )
			weights[i] = 1;
			
	for( int i = 0; i < (int)random_solutions.size(); i += nb_vars )
	{
		auto s = g( weights, random_solutions, i, i + nb_vars, nb_params, param_1, param_2 );
		
#if defined DEBUG
		std::copy( random_solutions.begin() + i, random_solutions.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << ": (0, " << s << ")\n";
#endif
		if( s != 0 )
			++cost;
	}
	
	for( int i = 0; i < (int)random_configurations.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( random_configurations.begin() + i, random_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		auto f = cost_map.at( convert( random_configurations, i, i + nb_vars ) );
		auto s = g( weights, random_configurations, i, i + nb_vars, nb_params, param_1, param_2 );
		cout << ": (" << f << ", " << s << ")\n";
		costs.emplace( f, s );
#else
		costs.emplace( cost_map.at( convert( random_configurations, i, i + nb_vars ) ),
		               g( weights, random_configurations, i, i + nb_vars, nb_params, param_1, param_2 ) );
#endif
	}
	
#if defined DEBUG
	cout << "\n//////////////\n\n";
	
	for( auto c : costs )
		cout << "(" << c.first << ", " << c.second << ")\n";
#endif
	
	for( auto it = costs.begin(); std::next( it ) != costs.end(); ++it )
	{
		if( (*it).second > (*std::next( it )).second )
			++cost;
	}

	return cost;
}
//-----------------------------------------------------------------------------
void main_function(int argc, char **argv)
{
	if( argc < 4 || argc > 6 )
	{
		usage( argv );
		return EXIT_FAILURE;
	}
	
	// all parameters are hard-coded!
	//const unsigned int SEED = 42;          // seed for random number generator
	const unsigned int SEED = time(0);
	const unsigned int T_SIZE = 3;        // size for tournament selection
	const unsigned int VEC_SIZE = number_units_transfo * number_units_compar + number_agregation_functions;    // Number of bits in genotypes
	const unsigned int POP_SIZE = 20;  // Size of population
	const unsigned int MAX_GEN = 100;  // Maximum number of generation before STOP
	const float CROSS_RATE = 0.8;          // Crossover rate
	const double P_MUT_PER_BIT = 0.01; // probability of bit-flip mutation
	const float MUT_RATE = 1.0;              // mutation rate
  //////////////////////////
	//  Random seed
	//////////////////////////
	//reproducible random seed: if you don't change SEED above, 
	// you'll aways get the same result, NOT a random run
	rng.reseed(SEED);


  //////////////////////////
	//  Initialization
	//////////////////////////
	nb_vars = stoi( argv[1] );
	max_value = stoi( argv[2] );
	precision = stod( argv[3] );
	if( argc > 4 )
	{
		param_1 = stoi( argv[4] );
		if( argc == 6 )
			param_2 = stoi( argv[5] );
	}
	nb_params = std::max(1, argc - 4);
	
#if defined AD
	concept = make_unique<AllDiffConcept>( nb_vars, max_value );
#elif defined LE
	// argv[3] is the right-hand side value of the equation
	concept = make_unique<LinearEqConcept>( nb_vars, max_value, param_1 );
#elif defined LT
	concept = make_unique<LessThanConcept>( nb_vars, max_value );	
#endif

	random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, precision );
	few_configurations.reserve( random_solutions.size() );
	std::copy( random_configurations.begin(),
	           random_configurations.begin() + random_solutions.size(),
	           few_configurations.begin() );

	cost_map = compute_metric_hamming_only( random_solutions, few_configurations, nb_vars );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";
	
	/////////////////////////////
	// Fitness function
	////////////////////////////
	// Evaluation: from a plain C++ fn to an EvalFunc Object
	eoEvalFuncPtr<Indi> eval(  fitness );
	////////////////////////////////
	// Initilisation of population
	////////////////////////////////
	// declare the population
	eoPop<Indi> pop;
	// fill it!
	for (unsigned int igeno=0; igeno<POP_SIZE; igeno++)
	{
		Indi v;                    // void individual, to be filled
		for (unsigned ivar=0; ivar<VEC_SIZE; ivar++)
		{
			bool r = rng.flip(); // new value, random in {0,1}
			v.push_back(r);          // append that random value to v
		}
		eval(v);                                // evaluate it
		pop.push_back(v);              // and put it in the population
	}
	// sort pop before printing it!
	pop.sort();
	// Print (sorted) intial population (raw printout)
	cout << "Initial Population" << endl;
	cout << pop;
	/////////////////////////////////////
	// selection and replacement
	////////////////////////////////////
	// The robust tournament selection
	eoDetTournamentSelect<Indi> select(T_SIZE);  // T_SIZE in [2,POP_SIZE]
	// The simple GA evolution engine uses generational replacement
	// so no replacement procedure is needed
	//////////////////////////////////////
	// The variation operators
	//////////////////////////////////////
	// 1-point crossover for bitstring
	eo1PtBitXover<Indi> xover;

	// standard bit-flip mutation for bitstring
	eoBitMutation<Indi>  mutation(P_MUT_PER_BIT);
	//////////////////////////////////////
	// termination condition
	/////////////////////////////////////
	// stop after MAX_GEN generations
	eoGenContinue<Indi> continuator(MAX_GEN);
 
	/////////////////////////////////////////
	// the algorithm
	////////////////////////////////////////
	// standard Generational GA requires as parameters
	// selection, evaluation, crossover and mutation, stopping criterion

	eoSGA<Indi> gga(select, xover, CROSS_RATE, mutation, MUT_RATE, 
	                eval, continuator);
	// Apply algo to pop - that's it!
	gga(pop);
 
	// Print (sorted) intial population
	pop.sort();
	cout << "FINAL Population\n" << pop << endl;
}
// A main that catches the exceptions
int main(int argc, char **argv)
{
#ifdef _MSC_VER
	//  rng.reseed(42);
	int flag = _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);
//    _CrtSetBreakAlloc(100);
#endif
	try
	{
		main_function(argc, argv);
	}
	catch(exception& e)
	{
		cout << "Exception: " << e.what() << '\n';
	}
	return 1;
}
