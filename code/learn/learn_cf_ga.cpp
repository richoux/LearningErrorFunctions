//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <sstream>

#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

// Command line option management
#include <argh.h>

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

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

using namespace std;

string constraint;
int nb_vars, max_value;
int samplings;
bool has_parameters;
vector<int> random_solutions;
vector<int> random_configurations;
unique_ptr<Concept> concept;
map<string, double> cost_map;
vector<double> params;
double params_value;
bool latin_sampling;
string input_file_path;
ifstream input_file;
string line, string_number;

randutils::mt19937_rng rng_utils;


void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -s NUMBER_SAMPLINGS [-p PARAMETERS] [-l]\n"
	     << "   OR: " << argv[0] << " -c {ad|le|lt|ol|cm} -i INPUT_FILE [-p PARAMETERS] [-l]\n"
	     << "Arguments:\n"
	     << "-h, --help\n"
	     << "-c, --constraint {ad|le|lt|ol|cm}\n"
	     << "-n, --nb_vars NB_VARIABLES\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN\n"
	     << "-s, --sampling NUMBER_SAMPLINGS\n"
	     << "-i, --input INPUT_FILE\n"
	     << "-p, --params PARAMETERS\n"
	     << "-l, --latin\n";
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
	
	for( int i = 0; i < (int)random_configurations.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( random_configurations.begin() + i, random_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = cost_map.at( convert( random_configurations, i, i + nb_vars ) );
		auto s = g( weights, params, random_configurations, max_value, i, nb_vars );

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

	// favor models with random operations
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
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-p", "--params" } );
	// argh::parser cmdl;
	// cmdl.add_param( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-p", "--params" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	// cout << cmdl( {"c", "constraint"} ).str() << " "
	//      << cmdl( {"n", "nb_vars"} ).str() << " "
	//      << cmdl( {"d", "max_domain"} ).str() << " "
	//      << cmdl( {"s", "sampling"} ).str() << " "
	//      << cmdl( {"p", "params"} ).str() << " "
	//      << cmdl( {"i", "input"} ).str() << "\n";
	
	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"d", "max_domain"} ) ) && !cmdl( {"i", "input"} ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	cmdl( {"n", "nb_vars"}, 9) >> nb_vars;
	cmdl( {"d", "max_domain"}, 9) >> max_value;
	cmdl( {"s", "sampling"}, 100) >> samplings;

	if( cmdl( {"p", "params"} ) )
		has_parameters = true;
	else
		has_parameters = false;
	cmdl( {"p", "params"}, 1.0 ) >> params_value;
	params = vector<double>( nb_vars, params_value );

	if( !( cmdl( {"c", "constraint"} ) >> constraint )
	    ||
	    ( constraint.compare("ad") != 0
	      && constraint.compare("le") != 0
	      && constraint.compare("lt") != 0
	      && constraint.compare("ol") != 0
	      && constraint.compare("cm") != 0 ) )
	{
		cerr << "Must provide a valid constraint among ad, le, lt, ol and cm. You provided '" << cmdl( {"c", "constraint"} ).str() << "'\n";
		usage( argv );
		return EXIT_FAILURE;
	}
	else
	{
		if( constraint.compare("ad") == 0 )
		{
			cout << "Constraint: AllDiff.\n";
			concept = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			cout << "Constraint: Linear equation.\n";
			concept = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}
		
		if( constraint.compare("lt") == 0 )
		{
			cout << "Constraint: Less than.\n";
			concept = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			cout << "Constraint: Overlap 1D.\n";
			concept = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}
	
	if( cmdl[ { "-l", "--latin" } ] )
		latin_sampling = true;
	else
		latin_sampling = false;

	if( cmdl( {"i", "input"} ) )
	{
		cout << "Loading data from " << input_file_path << "\n";

		cmdl( {"i", "input"} ) >> input_file_path;
		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number_samplings;
		int number;
		line_stream >> number_samplings;

		// loading solutions
		for( int i = 0; i < number_samplings; ++i )
		{
			getline( input_file, line );
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				random_solutions.push_back( number );
			}
		}
		
		// loading not solutions
		for( int i = 0; i < number_samplings; ++i )
		{
			getline( input_file, line );
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				random_configurations.push_back( number );
			}
		}
		
		input_file.close();
	}
	else
	{
		if( latin_sampling )
		{
			cout << "Perform Latin Hypercube sampling.\n";
			cap_draw( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
		else
		{
			cout << "Perform Monte Carlo sampling.\n";
			cap_draw_monte_carlo( concept, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
	}

	
	// all parameters are hard-coded!
	//const unsigned int SEED = 42;          // seed for random number generator
	const unsigned int SEED = time(0);
	const unsigned int T_SIZE = 3;        // size for tournament selection
	const unsigned int VEC_SIZE = number_units_transfo + number_units_compar + 2;    // Number of bits in genotypes
	const unsigned int POP_SIZE = 100;  // Size of population
	const unsigned int MAX_GEN = 150;  // Maximum number of generation before STOP
	const float CROSS_RATE = 0.8;          // Crossover rate
	const double onePointRate = 0.5;        // rate for 1-pt Xover
	const double P_MUT_PER_BIT = 0.05; // probability of bit-flip mutation
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
	
// #if defined DEBUG
// 	cout << "Random config: " << random_configurations.size() << "\n";	
// 	for( int i = 0; i < (int)random_configurations.size(); ++i )
// 	{
// 		if( i % nb_vars == 0 )
// 			cout << "\n";
// 		cout << random_configurations[i] << " ";
// 	}
// #endif
		
	cost_map = compute_metric_hamming_only( random_solutions, random_configurations, nb_vars );

	cout << "Number of variables: " << nb_vars
	     << "\nMax domain value: " << max_value
	     << "\nSampling samplings: " << samplings
	     << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n";

/////////////////
#if defined DEBUG
	Indi v2;
	vector<int> weights;
	
	if( constraint.compare("ad") == 0 )
		weights = vector<int>{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 };
	
	if( constraint.compare("lt") == 0 )
		weights = vector<int>{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	
	if( constraint.compare("le") == 0 )
		// weird function found with arguments "4 9 100.0 20"
		//vector<int> weights{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
		weights = vector<int>{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	
	if( constraint.compare("ol") == 0 )
		weights = vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 };
	
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
	//eo1PtBitXover<Indi> xover1;
	eoCFNQuadCrossover<Indi> xover1( number_units_transfo, number_units_arith, number_units_aggreg );
	eoPropCombinedQuadOp<Indi> xover( xover1, onePointRate );
	
	// standard bit-flip mutation for bitstring
	//eoBitMutation<Indi>  mutationBitFlip( P_MUT_PER_BIT );
	eoCFNMutation<Indi>  mutationBitFlip( number_units_transfo, number_units_compar, P_MUT_PER_BIT );
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
	cout << "Best individual: " << pop[0]
	     << "\nHas parameters: " << has_parameters
	     << "\nNumber of variables: " << nb_vars
	     << "\nMax domain value: " << max_value
	     << "\nNumber samplings: " << samplings
	     << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
	     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n\nModel:\n";

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
