//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout

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
#include "../utils/convert.hpp"
#include "../utils/randutils.hpp"

#include "../constraints/concept.hpp"
#if defined AD
#include "../constraints/all-diff_concept.hpp"
#elif defined LE
#include "../constraints/linear-eq_concept.hpp"
#elif defined LT
#include "../constraints/less-than_concept.hpp"
#elif defined CM
#include "../constraints/connection-min-gt_concept.hpp"
#elif defined OL
#include "../constraints/overlap-1d_concept.hpp"
#endif

using namespace std;

int nb_vars, max_value;
double precision;
bool has_parameters;
vector<int> random_solutions;
vector<int> random_configurations;
unique_ptr<Concept> concept;
vector<int> few_configurations;
map<string, double> cost_map;
vector<double> params;

randutils::mt19937_rng rng_utils;


void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " NB_VARIABLES MAX_VALUE PRECISION [Param]\n";
}

//-----------------------------------------------------------------------------
// define your individuals
typedef eoBit<eoMinimizingFitness> Indi;        // A bitstring with fitness double
//-----------------------------------------------------------------------------

bool no_parameter_operations( const vector<int>& weights )
{
	// test t4, t5, t6, t9, c1, c2, c3, c4
	return weights[4] == 0 && weights[5] == 0 && weights[6] == 0 && weights[9] == 0 && weights[13] == 0 && weights[14] == 0 && weights[15] == 0 && weights[16] == 0; 
}

string transfo_operation( int number )
{
	switch( number )
	{
	case 0:
		return "    Identity";
		break;
	case 1:
		return "Number of elements on the right equals to y";
		break;
	case 2:
		return "Number of elements on the right smaller than or equals to y";
		break;
	case 3:
		return "Number of elements on the right greater than or equals to y";
		break;
	case 4:
		return "Number of elements smaller than or equals to y + param";
		break;
	case 5:
		return "Number of elements greater than or equals to y + param";
		break;
	case 6:
		return "Max(0, param - y)";
		break;
	case 7:
		return "Max(0, x_i - x_i+1 )";
		break;
	case 8:
		return "Number of elements greater than or equals to y";
		break;
	case 9:
		return "Number of elements greater than or equals to y AND less than or equals to y + param";
		break;
	default:
		return "";
	}
}

string compar_operation( int number )
{
	switch( number )
	{
	case 0:
		return "    Identity";
		break;
	case 1:
		return "Input equals to parameter";
		break;
	case 2:
		return "Input greater than or equals to parameter";
		break;
	case 3:
		return "Input less than or equals to parameter";
		break;
	case 4:
		return "Euclidian division of the difference between input and parameter with domain size";
		break;
	default:
		return "";
	}	
}

void print_model( const Indi& indi )
{
	string arith = indi[ number_units_transfo ] ? "\t x" : "\t +";
	string agreg = indi[ number_units_transfo + 1 ] ? "       Sum" : "   Count #x > 0";
	auto number_active_transfo_units = std::count( indi.begin(), indi.begin() + number_units_transfo, true );
	
	for( int i = 0; i < number_units_transfo; ++i )
		if( indi[i] )
		{
			cout << transfo_operation(i) << "\n";
			if( --number_active_transfo_units > 0 )
				cout << arith << "\n";
		}

	cout << "\t|\n"
	     << "\tv\n"
	     << agreg << "\n"
	     << "\t|\n"
	     << "\tv\n";

	for( int i = 0; i < number_units_compar; ++i )
		if( indi[i + number_units_transfo + 2 ] )
		{
			cout << compar_operation(i) << "\n";
			break;
		}
}

eoMinimizingFitness fitness( const Indi& indi )
{
	// set< pair<double, double> > costs;
	double cost = 0.0;
	
	vector<int> weights( indi.size(), 0 );
	for( int i = 0; i < (int)indi.size(); ++i )
		if( indi[i] )
			weights[i] = 1;
			
	for( int i = 0; i < (int)random_solutions.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( random_solutions.begin() + i, random_solutions.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = cost_map.at( convert( random_solutions, i, i + nb_vars ) );
		auto s = g( weights, params, random_solutions, max_value, i, nb_vars );

		cost += std::abs( f - s );

		// costs.emplace( f, s );

		//sum_seconds += s;
#if defined DEBUG
		cout << "Hamming: " << f << "\n";
#endif
	}
	
	for( int i = 0; i < (int)few_configurations.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( few_configurations.begin() + i, few_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = cost_map.at( convert( few_configurations, i, i + nb_vars ) );
		auto s = g( weights, params, few_configurations, max_value, i, nb_vars );

		cost += std::abs( f - s );

		// costs.emplace( f, s );

#if defined DEBUG
		cout << "Hamming: " << f << "\n";
#endif
	}

	
	
	// penalize a network vector full of zeros
	if( std::count( weights.begin(), weights.begin() + number_units_transfo, 1 ) == 0 )
		cost += 10;
	// penalty if no unique agregation function
	if( std::count( std::prev( weights.end(), number_units_compar ), weights.end(), 1 ) != 1 )
		cost += 10;	
	// Huge penalty if the network does not use any operations with parameters although the user provides one (or some).
	if( has_parameters && no_parameter_operations( weights ) )
		cost += 1000;

	// favor models with few operations
	auto number_active_transfo_units = std::count( weights.begin(), weights.begin() + number_units_transfo, 1 );
	cost += ( static_cast<double>( number_active_transfo_units ) / number_units_transfo );

	return cost;

	// our score is cost_order + (cost_order / (variance+1)) + (cost_order * number_1), since cost_order is the most important metric
	// variance is here to forbid having all costs at the same value,
	// and minimizing the number of 1s in individuals is to keep the CPPN as simple as possible. 
	//return cost_order * (1 + 1.0/(1 + variance) + std::count( weights.begin(), weights.end(), 1) );

	// here the cost is cost_order + (cost_order * number_1)
	// return cost_order * (1 + std::count( weights.begin(), weights.end(), 1) );
}

// fix uncorrectly generated individuals
void fix( Indi& indi )
{
	// you need at least one active transformation unit
	if( std::count( indi.begin(), indi.begin() + number_units_transfo, 1 ) == 0 )
	{
		int index = rng_utils.uniform( 0, number_units_transfo - 1 );
		indi[ index ] = true;
	}

	// you need exactly one active comparison unit
	auto active_comparison = std::count( std::prev( indi.end(), number_units_compar ), indi.end(), 1 );
	if( active_comparison == 0 )
	{
		int index = rng_utils.uniform( number_units_transfo + 2, number_units_transfo + 1 + number_units_compar );
		indi[ index ] = true;
	}
	else
		if( active_comparison > 0 )
		{
			vector<int> indexes;
			for( int i = number_units_transfo + 2; i < number_units_transfo + 2 + number_units_compar; ++i )
				if( indi[ i ] )
					indexes.push_back( i );

			std::fill( std::prev( indi.end(), number_units_compar ), indi.end(), false );
			int index = rng_utils.pick( indexes );
			indi[ index ] = true;
		}
}

//-----------------------------------------------------------------------------
int main_function(int argc, char **argv)
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
	const unsigned int VEC_SIZE = number_units_transfo + number_units_compar + 2;    // Number of bits in genotypes
	const unsigned int POP_SIZE = 100;  // Size of population
	const unsigned int MAX_GEN = 200;  // Maximum number of generation before STOP
	const float CROSS_RATE = 0.8;          // Crossover rate
	const double onePointRate = 0.5;        // rate for 1-pt Xover
	const double P_MUT_PER_BIT = 0.01; // probability of bit-flip mutation
	const float MUT_RATE = 1.0;              // mutation rate
	const float REP_RATE = 0.5;				// replacement rate
	const double bitFlipRate = 0.5;          // rate for bit-flip mutation
	const double oneBitRate = 0.5;            // rate for one-bit mutation

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
		params = vector<double>( nb_vars, stod( argv[4] ) );
		has_parameters = true;
	}
	else
	{
		params = vector<double>( nb_vars, 1.0 );
		has_parameters = false;
	}
	
#if defined AD
	concept = make_unique<AllDiffConcept>( nb_vars, max_value );
#elif defined LE
	// params[0] is the right-hand side value of the equation
	concept = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
#elif defined LT
	concept = make_unique<LessThanConcept>( nb_vars, max_value );	
#elif defined CM
	concept = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );	
#elif defined OL
	concept = make_unique<Overlap1DConcept>( nb_vars, max_value, params );	
#endif

	random_draw( concept, nb_vars, max_value, random_solutions, random_configurations, precision );
	few_configurations.reserve( random_solutions.size() );
	std::copy( random_configurations.begin(),
	           random_configurations.begin() + random_solutions.size(),
	           std::back_inserter( few_configurations ) );

// #if defined DEBUG
// 	cout << "Few config: " << few_configurations.size() << "\n";	
// 	for( int i = 0; i < (int)few_configurations.size(); ++i )
// 	{
// 		if( i % nb_vars == 0 )
// 			cout << "\n";
// 		cout << few_configurations[i] << " ";
// 	}
// #endif
		
	cost_map = compute_metric_hamming_only( random_solutions, few_configurations, nb_vars );

	cout << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n";


/////////////////
#if defined DEBUG
	Indi v2;
#if defined AD
	vector<int> weights{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
#elif defined LT
	vector<int> weights{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
#elif defined LE
	// weird function found with arguments "4 9 100.0 20"
	//vector<int> weights{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
	vector<int> weights{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
#elif defined OL
	vector<int> weights{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 };
#endif
	for( auto& w : weights )
		v2.push_back( w );
	eoEvalFuncPtr<Indi> eval2( fitness );
	eval2(v2);
	cout << "Handmade individual: " << v2 << "\n\nModel:\n";
	print_model( v2 );
	return 1;
#endif
/////////////////
	
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
	
	// first individual with filled with zeros
	// Indi v;
	// for( unsigned ivar = 0; ivar < VEC_SIZE; ++ivar )
	// 	v.push_back( false );
	// fix(v);
	// eval(v);
	// pop.push_back(v);

	// // second special
	// vector<int> special{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	// Indi v2;
	// for( unsigned ivar = 0; ivar < VEC_SIZE; ++ivar )
	// 	if( special[ ivar ] == 0 )
	// 		v2.push_back( false );
	// 	else
	// 		v2.push_back( true );
	// eval(v2);
	// pop.push_back(v2);	
	
	// other individuals randomly filled.
	for( unsigned int igeno = 0; igeno < POP_SIZE; ++igeno )
	{
		Indi v;                    // void individual, to be filled

		for (unsigned ivar=0; ivar<VEC_SIZE; ivar++)
		{
			bool r = rng.flip(); // new value, random in {0,1}
			v.push_back(r);          // append that random value to v
		}

		fix(v);		
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
	eoDetTournamentSelect<Indi> selectOne(T_SIZE);            // T_SIZE in [2,POP_SIZE]
	// is now encapsulated in a eoSelectPerc (entage)
	eoSelectPerc<Indi> select( selectOne );// by default rate==1
	eoElitism<Indi> replace( REP_RATE );
	eoDetTournamentTruncate<Indi> tournament(T_SIZE);
	
	//////////////////////////////////////
	// The variation operators
	//////////////////////////////////////
	// 1-point crossover for bitstring
	eo1PtBitXover<Indi> xover1;
	eoPropCombinedQuadOp<Indi> xover( xover1, onePointRate );
	
	// standard bit-flip mutation for bitstring
	eoBitMutation<Indi>  mutationBitFlip( P_MUT_PER_BIT );
	// mutate exactly 1 bit per individual
	eoDetBitFlip<Indi> mutationOneBit;
	// Combine them with relative rates
	eoPropCombinedMonOp<Indi> mutation( mutationBitFlip, bitFlipRate );
	mutation.add( mutationOneBit, oneBitRate, true );
	
	// The operators are  encapsulated into an eoTRansform object
	eoSGATransform<Indi> transform( xover, CROSS_RATE, mutation, MUT_RATE );
	
	//////////////////////////////////////
	// termination conditions: use more than one
	/////////////////////////////////////
	// stop after MAX_GEN generations
	eoGenContinue<Indi> genCont( MAX_GEN );
	eoCombinedContinue<Indi> continuator( genCont );

	/////////////////////////////////////////
	// the algorithm
	////////////////////////////////////////
  // Easy EA requires
  // selection, transformation, eval, replacement, and stopping criterion
	eoEasyEA<Indi> gga( continuator, eval, select, transform, replace, tournament );

	// standard Generational GA requires as parameters
	// selection, evaluation, crossover and mutation, stopping criterion
	// eoSGA<Indi> gga(select, xover, CROSS_RATE, mutation, MUT_RATE, 
	//                 eval, continuator);

	// Apply algo to pop - that's it!
	gga(pop);
 
	// Print (sorted) intial population
	pop.sort();
	cout << "FINAL Population\n" << pop << endl;

	eval(pop[0]);
	cout << "Best individual: " << pop[0] << "\n"
	     << "number of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << random_solutions.size() * 100.0 / random_configurations.size() << "\n\nModel:\n";

	print_model( pop[0] );

	return EXIT_SUCCESS;
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
		return main_function(argc, argv);
	}
	catch(exception& e)
	{
		cout << "Exception: " << e.what() << '\n';
	}
}
