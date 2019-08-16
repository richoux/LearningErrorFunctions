#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <random>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <numeric>

#include <eo>
#include <es.h>

#include "utils.h"
#include "../all-diff.hpp"
#include "../increment.hpp"

using namespace std;

// REPRESENTATION
//-----------------------------------------------------------------------------
// define your individuals
typedef eoReal<double> Indi;

constexpr double PI = std::acos(-1);
constexpr double TWO_PI = 2*PI;

constexpr int MAX_DOMAIN = 8;
constexpr unsigned int NBER_VAR = 9; // 4
constexpr unsigned int NBER_FREQ = 10; // Number of frequencies composing our Fourier series
constexpr unsigned int VEC_SIZE = NBER_FREQ * NBER_VAR; // Number of object variables in genotypes


/***
 * The learned function is VERY sensitive to the length of the random walk!
 */
constexpr int LENGTH_RANDOM_WALK = /*  <<- Add/remove one '/' here to toggle active code block
    floor( sqrt( NBER_VAR * NBER_VAR ) ) + 1;
    /*/
    2*NBER_VAR;
    //*/

//-----------------------------------------------------------------------------
// Variables and target constraint 
vector<Variable> variables;

vector<reference_wrapper<Variable>> variables_ref;
AllDiff alldiff( variables_ref );

//-----------------------------------------------------------------------------
// Distributions
std::random_device rd{};
std::mt19937 gen{ rd() };
std::normal_distribution<> gaussian{ 0, std::sqrt( NBER_VAR ) };
std::uniform_int_distribution<> uniform_value{ 0, MAX_DOMAIN };
std::uniform_int_distribution<> uniform_variable{ 0, NBER_VAR - 1 };

//-----------------------------------------------------------------------------
// Trigonometric functions
double sine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 1.;
	else
		return sin( TWO_PI*k*x/max );
}

double cosine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 0.;
	else
		return cos( TWO_PI*k*x/max );
}

// EVAL
//-----------------------------------------------------------------------------
// Max l*mean(samples), with l the empirical correlation length.
// The goal is to learn the function f(x) = c(x).g(x), where
// c(x) is the concept of the target constraint.
// @param _indi A real-valued individual
double real_value( const Indi& indi )
{
	vector<double> g_outputs( LENGTH_RANDOM_WALK );
	vector<double> f_outputs( LENGTH_RANDOM_WALK );
	
	// random starting point
	for( auto v : variables_ref )
		v.get().set_value( uniform_value( gen ) );

	int number_of_non_solutions = 0;
	//std::cout << "Start!\n";
	
	for( int i = 0; i < LENGTH_RANDOM_WALK; ++i )
	{
		// Trace of the random walk
		// for( auto v : variables_ref )
		// 	std::cout << v.get().get_value() << " ";
		// std::cout << "\n";
				
		// evaluate g(x)
		double g_x = 0.;
		for( auto v : variables_ref )
		{
			for( unsigned int k = 0; k < NBER_FREQ; ++k )
				if( k%2 == 0 )
					g_x += ( indi[k] * cosine( v.get().get_value(), k, MAX_DOMAIN ) );
				else
					g_x += ( indi[k] * sine( v.get().get_value(), k, MAX_DOMAIN ) );
		}

		g_outputs[ i ] = std::abs( g_x );
		f_outputs[ i ] += std::abs( g_x ) * alldiff.cost();
		if( f_outputs[ i ] != 0 )
			++number_of_non_solutions;

		// new point from a random walk (local move)
		int var_to_change = uniform_variable( gen );
		int value_to_change;
		while( ( value_to_change = uniform_value( gen ) ) == variables_ref[ var_to_change ].get().get_value() ) {} // get a new value
		variables_ref[ var_to_change ].get().set_value( value_to_change );
	}

	double mean;
	double sum = 0.;
	for( int i = 0; i < LENGTH_RANDOM_WALK; ++i )
		sum += f_outputs[ i ];
	mean = sum / LENGTH_RANDOM_WALK;

	
	double mean_without_solutions = 0.;
	
	if( number_of_non_solutions == 0 )
		mean_without_solutions = mean;
	else
		mean_without_solutions = sum / number_of_non_solutions;
	
	double sum_diff_mean = 0.;
	double sum_diff_square = 0.;
	for( int i = 0; i < LENGTH_RANDOM_WALK - 1; ++i )
	{
		sum_diff_mean += ( ( f_outputs[ i ] - mean ) * ( f_outputs[ i + 1 ] - mean ) );
		sum_diff_square += std::pow( ( f_outputs[ i ] - mean ), 2 );
	}

	sum_diff_square += std::pow( ( f_outputs[ LENGTH_RANDOM_WALK - 1 ] - mean ), 2 );
	
	double empirical_autocorrelation_num = sum_diff_mean / ( LENGTH_RANDOM_WALK - 1 );
	double empirical_autocorrelation_den = sum_diff_square / LENGTH_RANDOM_WALK;
	double empirical_autocorrelation = empirical_autocorrelation_num / empirical_autocorrelation_den;
	double l = 1. / std::log( std::abs( empirical_autocorrelation ) );

	//return l * mean_without_solutions;
	return l;
}

// GENERAL
//-----------------------------------------------------------------------------
void main_function( int argc, char **argv )
{
// PARAMETRES
	// all parameters are hard-coded!
	// const unsigned int SEED = 42;   // seed for random number generator
	const unsigned int SEED = time(0);
	const unsigned int POP_SIZE = 100; // Size of population
	const unsigned int T_SIZE = 3;     // size for tournament selection
	const unsigned int MAX_GEN = 5000; // Maximum number of generation before STOP
	const float CROSS_RATE = 0.8;      // Crossover rate. Origin: 0.8
	const double EPSILON = 0.01;       // range for real uniform mutation. Origin: 0.01
	const float MUT_RATE = 0.5;        // mutation rate. Origin: 0.5 

	const int RANGE = 2; // random in [-RANGE, RANGE)

	// fill in variables
	for( int i = 0; i < NBER_VAR; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, NBER_VAR );
	for( int i = 0; i < NBER_VAR; ++i )
		variables_ref.emplace_back( variables[i] );

// GENERAL
	//////////////////////////
	//  Random seed
	//////////////////////////
	//reproducible random seed: if you don't change SEED above,
	// you'll aways get the same result, NOT a random run
	// rng.reseed(SEED);

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
			v.push_back( gaussian( gen ) );       // append a random value to v

		eval( v );                  // evaluate it
		pop.push_back( v );         // and put it in the population
	}
	// for( unsigned int igeno = 0; igeno < POP_SIZE; ++igeno )
	// {
	// 	Indi v;          // void individual, to be filled
	// 	for( unsigned ivar = 0; ivar < VEC_SIZE; ++ivar )
	// 	{
	// 		double r = 2*RANGE*rng.uniform() - RANGE; // new value, random in [-RANGE, RANGE)
	// 		v.push_back( r );       // append that random value to v
	// 	}
	// 	eval( v );                  // evaluate it
	// 	pop.push_back( v );         // and put it in the population
	// }

// OUTPUT
	// sort pop before printing it!
	//pop.sort();
	// Print (sorted) intial population (raw printout)
	//cout << "Initial Population" << endl;
	//cout << pop;

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

	cout << "\nBest population\n" << pop[0] << "\n";
	// cout << "\nTop 3 FINAL population\n"
	//      << pop[0] << "\n"
	//      << pop[1] << "\n"
	//      << pop[2] << "\n";

	// // Re-initialize all variables to 0
	// for( auto var : variables_ref )
	// 	var.get().set_value( 0 );

	// double g_x, f_x = 0.;
	
	// for( unsigned int k = 0; k < NBER_FREQ; ++k )
	// 	if( k%2 != 0 )
	// 		g_x += pop[0][k+2];

	// f_x = std::abs( g_x ) * alldiff.cost();

	// auto data = fetch_data( "../csv/all-diff_4.csv" );

	// for( auto var : variables_ref )
	// 	std::cout << var.get().get_value() << " ";

	// std::cout << "\nHand-made metric: " << data[0].cost
	//           << "\nLearned function: " << f_x << "\n\n";

	// int counter = 0;
	
	// // Big f*cking loop
	// // while all variable values are not equal to max_value
	// while( !std::all_of( variables_ref.begin(),
	//                      variables_ref.end(),
	//                      [&](auto var){ return var.get().get_value() == var.get().get_domain_max_value(); } ) )
	// {
	// 	increment( variables_ref );
	// 	++counter;

	// 	g_x = 0.;
		
	// 	for( auto v : variables_ref )
	// 	{
	// 		for( unsigned int k = 0; k < NBER_FREQ; ++k )
	// 			if( k%2 == 0 )
	// 				g_x += ( pop[0][k+2] * cosine( v.get().get_value(), k, MAX_DOMAIN ) );
	// 			else
	// 				g_x += ( pop[0][k+2] * sine( v.get().get_value(), k, MAX_DOMAIN ) );
	// 	}
		
	// 	f_x = std::abs( g_x ) * alldiff.cost();

	// 	for( auto var : variables_ref )
	// 		std::cout << var.get().get_value() << " ";
		
	// 	std::cout << "\nHand-made metric: " << data[counter].cost
	// 	          << "\nLearned function: " << f_x << "\n\n";
	// }
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
