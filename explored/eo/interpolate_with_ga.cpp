#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>

#include <eo>
#include <es.h>

#include "utils.h"

using namespace std;

// REPRESENTATION
//-----------------------------------------------------------------------------
// define your individuals
typedef eoReal<double> Indi;

constexpr double PI = std::acos(-1);
constexpr double TWO_PI = 2*PI;

constexpr int MAX_DOMAIN = 3;
constexpr unsigned int NBER_VAR = 1; // 4
constexpr unsigned int NBER_FREQ = 40; // Number of frequencies composing our Fourier series
constexpr unsigned int VEC_SIZE = NBER_FREQ * NBER_VAR; // Number of object variables in genotypes

double sine( double x, unsigned int k, int max )
{
	if( k == 0 )
		return 1.;
	else
		return sin( TWO_PI*k*x/max );
}

double cosine( double x, unsigned int k, int max )
{
	if( k == 0 )
		return 0.;
	else
		return cos( TWO_PI*k*x/max );
}


// EVAL
//-----------------------------------------------------------------------------
// try to fit to the choosen configuration space metric.
// @param _indi A real-valued individual
double real_value( const Indi& indi )
{
	auto data = fetch_data( "../csv/all-diff_4.csv" );
	
	double output_cost_function = 0;
	double cumul_error = 0;
	
	for( int i = 0; i < data.size(); ++i )
	{
		for( unsigned int k = 0; k < NBER_FREQ; ++k )
			if( k%2 == 0 )
				output_cost_function += ( indi[k] * cosine( i+1, k, data.size() ) );
			else
				output_cost_function += ( indi[k] * sine( i+1, k, data.size() ) );
		
		cumul_error += std::abs( output_cost_function - data[i].cost );
	}

	// for( auto sample : data )
	// {
	// 	for( auto value : sample.configuration )
	// 		for( unsigned int k = 0; k < NBER_FREQ; ++k )
	// 			if( k%2 == 0 )
	// 				output_cost_function += ( indi[k] * cosine( value, k, MAX_DOMAIN ) );
	// 			else
	// 				output_cost_function += ( indi[k] * sine( value, k, MAX_DOMAIN ) );

	// 	cumul_error += std::abs( output_cost_function - sample.cost );
	// }

	return -cumul_error; // negative since EO will try to maximize this value
	// return -( cumul_error / data.size() ); // negative since EO will try to maximize this value
}

// GENERAL
//-----------------------------------------------------------------------------
void main_function( int argc, char **argv )
{
// PARAMETRES
	// all parameters are hard-coded!
	// const unsigned int SEED = 42; // seed for random number generator
	const unsigned int SEED = time(0);
	const unsigned int POP_SIZE = 100; // Size of population
	const unsigned int T_SIZE = 3; // size for tournament selection
	const unsigned int MAX_GEN = 4000; // Maximum number of generation before STOP
	const float CROSS_RATE = 0.8; // Crossover rate. Origin: 0.8
	const double EPSILON = 0.01;  // range for real uniform mutation. Origin: 0.01
	const float MUT_RATE = 0.5;   // mutation rate. Origin: 0.5 

	const int RANGE = 2; // random in [-RANGE, RANGE)
	
// GENERAL
	//////////////////////////
	//  Random seed
	//////////////////////////
	//reproducible random seed: if you don't change SEED above,
	// you'll aways get the same result, NOT a random run
	rng.reseed(SEED);

// EVAL
	/////////////////////////////
	// Fitness function
	////////////////////////////
	// Evaluation: from a plain C++ fn to an EvalFunc Object
	eoEvalFuncPtr<Indi> eval( real_value );

// INIT
	////////////////////////////////
	// Initilisation of population
	////////////////////////////////

	// declare the population
	eoPop<Indi> pop;
	// fill it!
	for( unsigned int igeno = 0; igeno < POP_SIZE; ++igeno )
	{
		Indi v;          // void individual, to be filled
		for( unsigned ivar = 0; ivar < VEC_SIZE; ++ivar )
		{
			double r = 2*RANGE*rng.uniform() - RANGE; // new value, random in [-RANGE, RANGE)
			v.push_back( r );       // append that random value to v
		}
		eval( v );                  // evaluate it
		pop.push_back( v );         // and put it in the population
	}

// OUTPUT
	// sort pop before printing it!
	pop.sort();
	// Print (sorted) intial population (raw printout)
	cout << "Initial Population" << endl;
	// cout << pop;

// ENGINE
	/////////////////////////////////////
	// selection and replacement
	////////////////////////////////////

// SELECT
	// The robust tournament selection
	eoDetTournamentSelect<Indi> select( T_SIZE );       // T_SIZE in [2,POP_SIZE]

// REPLACE
	// eoSGA uses generational replacement by default
	// so no replacement procedure has to be given

// OPERATORS
	//////////////////////////////////////
	// The variation operators
	//////////////////////////////////////

// CROSSOVER
	// offspring(i) is a linear combination of parent(i)
	eoSegmentCrossover<Indi> xover;

// MUTATION
	// offspring(i) uniformly chosen in [parent(i)-epsilon, parent(i)+epsilon]
	eoUniformMutation<Indi>  mutation( EPSILON );

// STOP
// CHECKPOINT
	//////////////////////////////////////
	// termination condition
	/////////////////////////////////////
	// stop after MAX_GEN generations
	eoGenContinue<Indi> continuator( MAX_GEN );

// GENERATION
	/////////////////////////////////////////
	// the algorithm
	////////////////////////////////////////
	// standard Generational GA requires
	// selection, evaluation, crossover and mutation, stopping criterion
	eoSGA<Indi> gga( select, xover, CROSS_RATE, mutation, MUT_RATE,
	                 eval, continuator );

	// Apply algo to pop - that's it!
	gga( pop );

// OUTPUT
	// Print (sorted) intial population
	pop.sort();
// GENERAL

	cout << "\nCosts\n";
	auto data = fetch_data( "../csv/all-diff_4.csv" );
	double output_cost_function;
	double double_check = 0.;

	
	for( int i = 0; i < data.size(); ++i )
	{
		for( unsigned int k = 0; k < NBER_FREQ; ++k )
			if( k%2 == 0 )
				output_cost_function += ( pop[0][k] * cosine( i+1, k, data.size() ) );
			else
				output_cost_function += ( pop[0][k] * sine( i+1, k, data.size() ) );
		
		std::copy( data[i].configuration.begin(),
		           data[i].configuration.end(),
		           std::ostream_iterator<int>(std::cout, " ") );
		cout << "=> " << data[i].cost << " | " << output_cost_function << "\n";

		double_check += std::abs( data[i].cost - output_cost_function );
	}

	// for( auto sample : data )
	// {
	// 	for( auto value : sample.configuration )
	// 		for( unsigned int k = 0; k < NBER_FREQ; ++k )
	// 			if( k%2 == 0 )
	// 				output_cost_function += ( pop[0][k] * cosine( value, k, MAX_DOMAIN ) );
	// 			else
	// 				output_cost_function += ( pop[0][k] * sine( value, k, MAX_DOMAIN ) );

	// 	std::copy( sample.configuration.begin(),
	// 	           sample.configuration.end(),
	// 	           std::ostream_iterator<int>(std::cout, " ") );
	// 	cout << "=> " << sample.cost << " | " << output_cost_function << "\n";

	// 	double_check += std::abs( sample.cost - output_cost_function );
	// }

	cout << "\nFINAL Population\n" << pop[0]
	     << "\nDouble check: " << double_check << "\n";
	//<< "\nDouble check: " << double_check/data.size() << "\n";
}

// A main that catches the exceptions
int main( int argc, char **argv )
{
	try
	{
		main_function( argc, argv );
	}
	catch(exception& e)
	{
		cout << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
