//-----------------------------------------------------------------------------
// standard includes
#include <stdexcept>  // runtime_error 
#include <iostream>    // cout
#include <sstream>

#include <ctime>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <set>

// Command line arguments manager
#include <argh.h>

// the general include for eo
#include <eo>
#include <ga.h>

// code from the CFN version
//-----------------------------------------------------------------------------
#include "function_to_learn_icn.hpp" // for number_functions

#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"
#include "../utils/random_draw.hpp"
#include "../utils/convert.hpp"
#include "../utils/print.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/linear-leq_concept.hpp"
#include "../constraints/linear-geq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

using namespace std;

string constraint;
int nb_vars, max_value;
int samplings;
bool do_samplings = false;
int training_size;
bool has_parameters;
vector<int> random_solutions;
vector<int> random_configurations;
unique_ptr<Concept> concept_;
map<string, pair<double,double>> cost_map;
vector<double> params;
double params_value;
bool latin_sampling;
string input_file_path;
ifstream input_file;
ifstream input_costs_file;
string line, string_number;
int number_configurations_in_file;
bool xp;
bool debug;
bool hyperparameters_tuning;

// GA hyper-parameters
unsigned int SEED;
unsigned int T_SIZE;   // size for tournament selection
unsigned int VEC_SIZE; // Number of bits in genotypes
unsigned int POP_SIZE; // Size of population
unsigned int STEADY_GEN;  // Number of generations with no improvements before STOP
unsigned int MIN_GEN;  // Minimum number of generation before STOP
float CROSS_RATE;      // Crossover rate
float MUT_RATE;        // mutation rate
float REP_RATE;				 // replacement rate

randutils::mt19937_rng rng_utils;

void usage( char **argv )
{
	cout << "Usage: " << argv[0] << " -c {ad|le|ll|lg|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -s NUMBER_SAMPLINGS [-p PARAMETERS] [-l] [--xp]\n"
	     << "   OR: " << argv[0] << " -c {ad|le|ll|lg|lt|ol|cm} -n NB_VARIABLES -d MAX_VALUE_DOMAIN -i INPUT_FILE -ci COMPLETE_INPUT_FILE [-p PARAMETERS] [--xp]\n"
	     << "Arguments:\n"
	     << "-h, --help, printing this message.\n"
	     << "-c, --constraint {ad|le|ll|lg|lt|ol|cm}, respectively for AllDiff, Linear equation, Linear inequation <=, Linear inequation >=, Less than, Overlap 1D and Connection minimum.\n"
	     << "-n, --nb_vars NB_VARIABLES, the number of variables in the constraint.\n"
	     << "-d, --max_domain MAX_VALUE_DOMAIN, the maximal value variables can take.\n"
	     << "-s, --sampling NUMBER_SAMPLINGS, the number of required solutions and non-solutions.\n"
	     << "-i, --input INPUT_FILE containing sampled configurations.\n"
	     << "-ci, --complete_input COMPLETE_INPUT_FILE containing the full configuration space.\n"
	     << "-p, --params PARAMETERS, the list of parameters required.\n"
	     << "-l, --latin for performing Latin Hypercube samplings instead of Monte Carlo samplings.\n"
	     << "--xp to print on the screen results for experiments only.\n"
	     << "--paramILS to print on the screen hyperparameters tuning with paramILS.\n"
	     << "--tournament T_SIZE, size for tournament selection.\n"
	     << "--pop POP_SIZE, size of the population.\n"
	     << "--steady STEADY_GEN, number of generations with no improvements before stopping the learning.\n"
	     << "--mingen MIN_GEN, minimum number of generation before stopping the learning.\n"
	     << "--crossover CROSS_RATE, the crossover rate in [0,1].\n"
	     << "--mutation MUT_RATE, the mutation rate in [0,1]\n"
	     << "--replacement REP_RATE, the replacement rate in [0,1].\n"
	     << "--seed SEED, the seed for the pseudo-random generator.\n"
	     << "--debug.\n";
}

//-----------------------------------------------------------------------------
// define your individuals
typedef eoBit<eoMinimizingFitness> Indi;        // A bitstring with fitness double
//-----------------------------------------------------------------------------

bool no_parameter_operations( const vector<int>& weights )
{
	// test t7, t8, t9, t10, t11, t17, c1, c2, c3, c4
	return weights[7] == 0 && weights[8] == 0 && weights[9] == 0 && weights[10] == 0 && weights[11] == 0 && weights[17] == 0 && weights[21] == 0 && weights[22] == 0 && weights[23] == 0 && weights[24] == 0; 
}

// The fitness outputs a cost corresponding to the best of these two metrics:
// 1. the Hamming metric, i.e., the sum of the difference between
// the expected Hamming distance and the predicted Hamming distance for each configuration
// of the training set (solutions + non-solutions),
// 2. or the Manhattan metrics, i.e., the sum of the difference between
// the expected Manhattan distance and the predicted Manhattan distance for each configuration
// of the training set (solutions + non-solutions).
// 
// Those are the sums, NOT the averages. Individual costs are normalized in [0,1], but the final cost
// is normalized latter in the program.
// A penalty in [0,1[ to favor shorter models is also added just before returning the cost. 
eoMinimizingFitness fitness( const Indi& indi )
{
	double sum_costs_hamming = 0.0;
	double sum_costs_manhattan = 0.0;
	
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

		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << "\n";
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

		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << "\n";
#endif
	}

	// Normalizing individual cost (after computing the sums, but it doesn't matter)
	// This is to have a fair comparison between Hamming and Manhattan costs,
	// otherwise Hamming would always be the smallest one.
	// Normalization for Hamming: division by the number of variables
	// Normalization for Manhattan: division by the number of variables times the maximal gap of values (here, max_value - min_value = max_value - 1)
	sum_costs_hamming /= nb_vars;
	sum_costs_manhattan /= ( nb_vars * ( max_value - 1 ) );
	
	double final_cost = std::min( sum_costs_hamming, sum_costs_manhattan );
	
	// penalize a network vector full of zeros
	if( std::count( weights.begin(), weights.begin() + number_units_transfo, 1 ) == 0 )
		final_cost += ( 10 * training_size );
	// penalty if no unique comparison function
	if( std::count( std::prev( weights.end(), number_units_compar ), weights.end(), 1 ) != 1 )
		final_cost += ( 10 * training_size );	
	// Huge penalty if the network does not use any operations with parameters although the user provides one (or some),
	// or if there is at least one operation with parameters although the user did not provide any.
	if( ( has_parameters && no_parameter_operations( weights ) ) || ( !has_parameters && !no_parameter_operations( weights ) ) )
		final_cost += ( 1000 * training_size );

	// favor models with fewer operations
	auto number_active_transfo_units = std::count( weights.begin(), weights.begin() + number_units_transfo, 1 );
	final_cost += ( static_cast<double>( number_active_transfo_units ) / number_units_transfo );

	return final_cost;
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
	auto start = std::chrono::steady_clock::now();
	number_configurations_in_file = 0;
	
	argh::parser cmdl( { "-c", "--constraint", "-n", "--nb_vars", "-d", "--max_domain", "-s", "--sampling", "-i", "--input", "-ci", "--complete_input", "-p", "--params", "--tournament", "--pop", "--steady", "--mingen", "--crossover", "--mutation", "--replacement", "--seed" } );
	cmdl.parse( argc, argv );
	
	if( cmdl[ { "-h", "--help"} ] )
	{
		usage( argv );
		return EXIT_SUCCESS;
	}

	if( !( cmdl( {"n", "nb_vars"} ) && cmdl( {"d", "max_domain"} ) ) )
	{
		usage( argv );
		return EXIT_FAILURE;
	}

	if( cmdl( {"i", "input"} ) && cmdl( {"ci", "complete_input"} ) )
	{
		cerr << "You cannot provide both an input file and a complete input file at the same time.\n";
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

	if( cmdl[ { "--xp" } ] )
		xp = true;
	else
		xp = false;
		
	if( cmdl[ { "--debug" } ] )
		debug = true;
	else
		debug = false;

	if( cmdl[ { "--paramILS" } ] )
		hyperparameters_tuning = true;
	else
		hyperparameters_tuning = false;

	if( !( cmdl( {"c", "constraint"} ) >> constraint )
	    ||
	    ( constraint.compare("ad") != 0
	      && constraint.compare("le") != 0
	      && constraint.compare("ll") != 0
	      && constraint.compare("lg") != 0
	      && constraint.compare("lt") != 0
	      && constraint.compare("ol") != 0
	      && constraint.compare("cm") != 0 ) )
	{
		cerr << "Must provide a valid constraint among ad, le, ll, lg, lt, ol and cm. You provided '" << cmdl( {"c", "constraint"} ).str() << "'\n";
		usage( argv );
		return EXIT_FAILURE;
	}
	else
	{
		if( constraint.compare("ad") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: AllDiff.\n";
			concept_ = make_unique<AllDiffConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("le") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear equation.\n";
			concept_ = make_unique<LinearEqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("ll") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear inequation <=.\n";
			concept_ = make_unique<LinearLeqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("lg") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Linear inequation >=.\n";
			concept_ = make_unique<LinearGeqConcept>( nb_vars, max_value, params[0] );
		}

		if( constraint.compare("lt") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Less than.\n";
			concept_ = make_unique<LessThanConcept>( nb_vars, max_value );
		}
		
		if( constraint.compare("ol") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Overlap 1D.\n";
			concept_ = make_unique<Overlap1DConcept>( nb_vars, max_value, params );
		}
		
		if( constraint.compare("cm") == 0 )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Constraint: Connection Minimum (greater-than version).\n";
			concept_ = make_unique<ConnectionMinGTConcept>( nb_vars, max_value, params[0] );
		}
	}
	
	if( cmdl[ { "-l", "--latin" } ] )
		latin_sampling = true;
	else
		latin_sampling = false;

	if( cmdl( {"i", "input"} ) )
	{
		cmdl( {"i", "input"} ) >> input_file_path;

		if( !xp && !hyperparameters_tuning )
			cout << "Loading data from " << input_file_path << "\n";

		input_file.open( input_file_path );

		getline( input_file, line );
		stringstream line_stream( line );
		int number;
		line_stream >> number_configurations_in_file;

		// loading solutions
		for( int i = 0; i < number_configurations_in_file; ++i )
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
		for( int i = 0; i < number_configurations_in_file; ++i )
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

		number_configurations_in_file *= 2;
		input_file.close();
	}
	else if( cmdl( {"ci", "complete_input"} ) )
	{
		cmdl( {"ci", "complete_input"} ) >> input_file_path;

		if( !xp && !hyperparameters_tuning )
			cout << "Loading data from " << input_file_path << "\n";
		
		input_file.open( input_file_path );

		int number;
		
		// loading solutions/configurations
		while( getline( input_file, line ) )
		{
			++number_configurations_in_file;
			auto delimiter = line.find(" : ");
			std::string solution_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 3 );
			
			stringstream line_stream( line );
			while( line_stream >> string_number )
			{
				stringstream number_stream( string_number );
				number_stream >> number;
				if( solution_token.compare("1") == 0 )
					random_solutions.push_back( number );
				else
					random_configurations.push_back( number );					
			}
		}		

		input_file.close();
	}
	else
	{
		do_samplings = true;
		if( latin_sampling )
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Perform Latin Hypercube sampling.\n";
			cap_draw( concept_, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
		else
		{
			if( !xp && !hyperparameters_tuning )
				cout << "Perform Monte Carlo sampling.\n";
			cap_draw_monte_carlo( concept_, nb_vars, max_value, random_solutions, random_configurations, samplings );
		}
	}

	cmdl( {"tournament"}, 2) >> T_SIZE;
	cmdl( {"pop"}, 100) >> POP_SIZE;
	cmdl( {"steady"}, 5) >> STEADY_GEN;
	cmdl( {"mingen"}, 200) >> MIN_GEN;
	cmdl( {"crossover"}, 0.8) >> CROSS_RATE;
	cmdl( {"mutation"}, 1.0) >> MUT_RATE;
	cmdl( {"replacement"}, 0.05) >> REP_RATE;
	cmdl( {"seed"}, time(0)) >> SEED;
	////////////////////////////
	//  Arguments parsing over
	////////////////////////////

	VEC_SIZE = number_units_transfo + number_units_compar + number_units_aggreg + number_units_arith;
	rng.reseed(SEED);


	if( cmdl( {"i", "input"} ) || cmdl( {"ci", "complete_input"} ) )
	{
		double manhattan_cost;
		std::string input_costs_file_path = input_file_path.substr( 0, input_file_path.length() - 4 ) + std::string("_costs.txt");

		input_costs_file.open( input_costs_file_path );
		while( getline( input_costs_file, line ) )
		{
			auto delimiter = line.find(" ");
			std::string solution_token = line.substr( 0, delimiter );
			line.erase(0, delimiter + 1 );
			delimiter = line.find(" ");
			std::string hamming_cost = line.substr( 0, delimiter );
			line.erase(0, delimiter + 1 );
			stringstream line_stream( line );
			line_stream >> manhattan_cost;
			cost_map.emplace( solution_token, std::pair<double,double>( std::stod( hamming_cost ), manhattan_cost ) );
		}
		
		input_costs_file.close();
	}
	else
		cost_map = compute_metric_hamming_and_manhattan( random_solutions, random_configurations, nb_vars );

	training_size = number_configurations_in_file == 0 ? samplings*2 : number_configurations_in_file;	

	if( !xp && !hyperparameters_tuning )
	{
		cout << "Number of variables: " << nb_vars
		     << "\nMax domain value: " << max_value;

		cout << "\nTotal number of training configurations: " << training_size;
		if( do_samplings )
			cout << " (sampled)";
		cout << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
		     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n";
	}

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
	eoEvalFuncPtr<Indi> eval( fitness );

	////////////////////////////////
	// Initilisation of population
	////////////////////////////////
	// declare the population
	eoPop<Indi> pop;
	// fill it!
	
	for( unsigned int igeno = 0; igeno < POP_SIZE; ++igeno )
	{
		Indi v;                    // void individual, to be filled

		for( unsigned ivar = 0; ivar < VEC_SIZE; ++ivar )
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

  // print (sorted) intial population (raw printout)
	if( !xp && !hyperparameters_tuning )
		cout << "Initial Population\n" << pop;

	/////////////////////////////////////
	// selection and replacement
	////////////////////////////////////
	// The robust tournament selection
	eoDetTournamentSelect<Indi> selectOne( T_SIZE );            // T_SIZE in [2,POP_SIZE]
	// is now encapsulated in a eoSelectPerc (entage)
	eoSelectPerc<Indi> select( selectOne );// by default rate==1
	eoElitism<Indi> replace( REP_RATE );
	eoDetTournamentTruncate<Indi> tournament( T_SIZE );
	
	//////////////////////////////////////
	// The variation operators
	//////////////////////////////////////
	// 1-point crossover for bitstring
	eoCFNQuadCrossover<Indi> xover( number_units_transfo, number_units_arith, number_units_aggreg );
	
	// homemade bit-flip mutation for bitstring to satify some constraints
	eoCFNMutation<Indi>  mutationBitFlip( number_units_transfo, number_units_compar );
	
	// The operators are  encapsulated into an eoTRansform object
	eoSGATransform<Indi> transform( xover, CROSS_RATE, mutationBitFlip, MUT_RATE );
	
	//////////////////////////////////////
	// termination conditions: use more than one
	/////////////////////////////////////
	// stop after MAX_GEN generations
	// eoGenContinue<Indi> genCont( MAX_GEN );

	// does a minimum number of generations, then stops whenever a given number of generations takes place without improvement.
	eoSteadyFitContinue<Indi> steadyFit( MIN_GEN, STEADY_GEN); 
	eoCombinedContinue<Indi> continuator( steadyFit );

	if( debug )
	{
		// but now you want to make many different things every generation 
		// (e.g. statistics, plots, ...).
		// the class eoCheckPoint is dedicated to just that:
		// Declare a checkpoint (from a continuator: an eoCheckPoint 
		// IS AN eoContinue and will be called in the loop of all algorithms)
		eoCheckPoint<Indi> checkpoint(continuator);

		// Create a counter parameter
		eoValueParam<unsigned> generationCounter( 0, "Gen." );

		// Create an incrementor (sub-class of eoUpdater). Note that the 
		// parameter's value is passed by reference, 
		// so every time the incrementer is updated (every generation),
		// the data in generationCounter will change.
		eoIncrementor<unsigned> increment( generationCounter.value() );
		// Add it to the checkpoint, 
		// so the counter is updated (here, incremented) every generation
		checkpoint.add( increment );
		// now some statistics on the population:
		// Best fitness in population
		eoBestFitnessStat<Indi> bestStat;
		// Second moment stats: average and stdev
		eoSecondMomentStats<Indi> SecondStat;
		// Add them to the checkpoint to get them called at the appropriate time
		checkpoint.add( bestStat );
		checkpoint.add( SecondStat );
		// // The Stdout monitor will print parameters to the screen ...
		// eoStdoutMonitor monitor();

		// // when called by the checkpoint (i.e. at every generation)
		// checkpoint.add(monitor);
		// // the monitor will output a series of parameters: add them 
		// monitor.add(generationCounter);
		// monitor.add(eval); // because now eval is an eoEvalFuncCounter!
		// monitor.add(bestStat);
		// monitor.add(SecondStat);
		// A file monitor: will print parameters to ... a File, yes, you got it!
		eoFileMonitor fileMonitor( "stats.xg", " " );

		// the checkpoint mechanism can handle multiple monitors
		checkpoint.add( fileMonitor );
		// the fileMonitor can monitor parameters, too, but you must tell it!
		fileMonitor.add( generationCounter );
		fileMonitor.add( bestStat );
		fileMonitor.add( SecondStat );
		// Last type of item the eoCheckpoint can handle: state savers:
		eoState outState;
		// Register the algorithm into the state
		outState.registerObject( pop );
		outState.registerObject( rng );
		// and feed the state to state savers
    // save state every 40th  generation
		eoCountedStateSaver stateSaver1( 50, outState, "generation" ); 
		// save state every 1 seconds 
		eoTimedStateSaver stateSaver2( 1, outState, "time" ); 
		// Don't forget to add the two savers to the checkpoint
		checkpoint.add( stateSaver1 );
		checkpoint.add( stateSaver2 );
		// and that's it for the (control and) output

		continuator = checkpoint;
	}
	
	/////////////////////////////////////////
	// the algorithm
	////////////////////////////////////////
  // Easy EA requires
  // selection, transformation, eval, replacement, and stopping criterion
	eoEasyEA<Indi> gga( continuator, eval, select, transform, replace, tournament );

	// Apply algo to pop - that's it!
	gga( pop );
 
	// Print (sorted) intial population
	pop.sort();
	if( !xp && !hyperparameters_tuning )
		cout << "FINAL Population\n" << pop << "\n";

	auto best_fitness = pop[0].fitness();
	int number_ex_aequo;
	for( number_ex_aequo = 0 ; pop[number_ex_aequo].fitness() == best_fitness ; ++number_ex_aequo ) ; // empty loop

	std::map<std::string,int> count_vectors;
	for( int i = 0; i < number_ex_aequo ; ++i )
	{
		std::ostringstream vector_stream;
		std::copy(pop[i].begin(), pop[i].end(), std::ostream_iterator<bool>(vector_stream, ""));
		++count_vectors[ vector_stream.str() ];
	}

	std::string more_frequent_vector;
	int highest_frequency = 0;
	
	for( auto& m : count_vectors )
		if( highest_frequency < m.second )
		{
			highest_frequency = m.second;
			more_frequent_vector = m.first;
		}

	int fitness_integer = static_cast<int>( floor( best_fitness ) );
	double regularization_term = best_fitness - fitness_integer;
	
	if( xp )
		cout << static_cast<double>( fitness_integer ) / training_size << " " << highest_frequency << " " << more_frequent_vector << "\n";
	else
		// Warning: for hyperparameter tuning experiments done in December 2020, training_size had not been doubled.
		// But this didn't impact those experiments since it didn't change the fitness ordering. However, fitness training
		// were actually better than the one in those experiments result files (recall: for hyperparameter tuning only)
		if( hyperparameters_tuning )
		{
			auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>( std::chrono::steady_clock::now() - start ).count();

			cout << "final quality is " << static_cast<double>( fitness_integer ) / training_size << "\n"
			     << "runtime is " << elapsed_time << "\n"
			     << "seed is " << SEED << "\n"
			     << "SUCCESS\n";
		}
		else
		{
			cout << "Best individual (frequency): " << more_frequent_vector << " (" << highest_frequency << ")"
			     << "\nFitness on the whole training set: " << fitness_integer
			     << "\nRegularization term: " << regularization_term
			     << "\nMean fitness: " << static_cast<double>( fitness_integer ) / training_size
			     << "\nNormalized mean fitness: " << ( static_cast<double>( fitness_integer ) / training_size ) / nb_vars
			     << "\nHas parameters: " << ( has_parameters ? "true" : "false" )
			     << "\nNumber of variables: " << nb_vars
			     << "\nMax domain value: " << max_value
			     << "\nNumber of training configurations: " << training_size;
			if( do_samplings )
				cout << " (sampled)";

			cout << "\nNumber of solutions: " << random_solutions.size() / nb_vars << ", density = "
			     << static_cast<double>( random_solutions.size() ) / ( random_configurations.size() + random_solutions.size() ) << "\n\nModel:\n";
			
			int index;
			for( index = 0; index < number_ex_aequo ; ++index )
			{
				std::ostringstream vector_stream;
				std::copy(pop[index].begin(), pop[index].end(), std::ostream_iterator<bool>(vector_stream, ""));
				if( vector_stream.str().compare( more_frequent_vector ) == 0 )
					break;
			}
		
			print_model( pop[index] );
		}

	return EXIT_SUCCESS;
}

// A main that catches the exceptions
int main(int argc, char **argv)
{
	try
	{
		return main_function( argc, argv );
	}
	catch(exception& e)
	{
		cout << "Exception: " << e.what() << '\n';
	}
}
