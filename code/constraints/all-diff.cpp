#include <cmath>
#include <complex>
#include <algorithm>

#include "all-diff.hpp"

constexpr int NB_VARS = 9;
constexpr int MAX_DOMAIN = NB_VARS - 1;
constexpr	double MAX_COST = NB_VARS + ( MAX_DOMAIN / ( std::pow( 10, std::floor( std::log10( MAX_DOMAIN ) ) + 1 ) ) );

// Trigonometric functions
//constexpr double PI = std::acos(-1);
constexpr double PI = M_PI;
constexpr double TWO_PI = 2*PI;

double sine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 1.;
	else
		return sin( TWO_PI*k*x/( max + 1) );
}

double cosine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 0.;
	else
		return cos( TWO_PI*k*x/( max + 1 ) );
}

inline complex<double> expo( double x, unsigned int k, int max )
{
	return complex<double>( cosine( x, k, max ), sine( x, k, max ) );
}

////////////////////

// defined in cfn/function_to_learn_cppn.cpp
void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& result );

///////////////////////////////////////////

// AllDiff concept 
bool alldiff_concept( const vector< reference_wrapper<Variable> >& variables )
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < variables.size() ; ++i )
		if( !bitvec[ variables[i].get().get_value() ] )
			bitvec[ variables[i].get().get_value() ] = true;
		else
			return false;
	
	return true;
}

//////////////////////////////////////////////////////

AllDiff::AllDiff( const vector< reference_wrapper<Variable> >& variables )
	: Constraint (variables)
{ }

// AllDiff concept as a cost function
#if defined CONCEPT
double AllDiff::required_cost() const
{
	// We assume our k variables can take values in [0, k-1]
	vector<bool> bitvec( variables.size(), false );

	// If we have two variables sharing the same value, return 1 (not a solution)
	// otherwise, return 0.
	for( int i = 0 ; i < variables.size() ; ++i )
		if( !bitvec[ variables[i].get().get_value() ] )
			bitvec[ variables[i].get().get_value() ] = true;
		else
			return 1;
	
	return 0;
}
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// SOFT_ALLDIFF cost function (Petit et al. 2001)
#if defined SOFT
double AllDiff::required_cost() const
{
	double counter = 0;
	
	for( int i = 0 ; i < variables.size() - 1 ; ++i )
		for( int j = i + 1 ; j < variables.size() ; ++j )
			if( variables[i].get().get_value() == variables[j].get().get_value() )
				++counter;

	return counter;
}
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// Handmade
#if defined HANDMADE
double AllDiff::required_cost() const
{
	double counter = 0;
	int occurences;
	
	for( int i = 0; i < variables[0].get().get_domain_size(); ++i )
	{
		occurences = std::count_if( variables.begin(), variables.end(), [&](auto v){ return v.get().get_value() == i; } );
		if( occurences > 1 )
			counter += occurences;
	}

	return counter;
}
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// Learned cost function with GA for all-diff 9
#if defined GA
double AllDiff::required_cost() const
{
	if( alldiff_concept( variables ) )
		return 0.;
	
	double g_x = 0.;
	
	// l + mean
	// vector<double> coeff{0.583181, -0.200416, 1.17494, -0.31438, -0.0510316, -0.126238, -0.577367, -0.319095, 0.0890565, -0.180456, -0.15967, -0.471476, 0.0287462, -0.751347, -0.0198749, -1.54704, 0.0971736, 0.0881159, 1.15391, 0.776695, -0.294099, 0.093463, 0.0565593, 0.360842, 0.24014, 0.0677739, -0.199163, -1.36252, 1.06668, -1.9583, -0.161077, 1.51144, -1.49068, 0.504876, -0.240177, -0.71764, -1.50791, -1.4551, -0.474137, -1.15966, 0.583789, -0.453789, 0.178955, 0.463795, 0.858367, 1.04083, -0.112922, -0.353993, -0.594024, -0.631471, -0.97812, -0.654888, -0.0526192, -1.52583, -1.63348, -0.496767, 0.716332, -2.03085, -0.374755, 1.11972, 0.742286, 0.409111, -0.350915, 0.014417, 1.11912, 0.690953, 0.837182, -1.70437, -1.06024, -0.458516, 0.654111, -0.302674, 1.42033, -1.03297, 1.03075, 0.562125, -1.20907, 0.175022, 0.145007, 0.524922, -1.45185, 0.732606, 0.303118, -0.651637, -1.05189, -0.328604, 0.572037, -0.183545, -1.11304, -1.53877};

	// l
	vector<double> coeff{-1.06773, -0.102726, 0.271846, 0.124164, -0.902654, -0.405455, -0.0734149, -0.8937, 0.190613, -0.153659, 0.443931, 0.515271, -0.614809, -0.775251, 0.81307, -0.800964, 1.00042, -0.557859, 0.466797, -0.26307, -0.329014, -0.255394, 1.00122, -1.41409, -0.526326, 0.349372, -0.761743, 0.760383, 0.572062, 0.223655, -0.327689, 0.452602, -0.814645, -0.563959, -0.166153, -0.465961, 1.13372, 0.365034, -0.963438, 0.0527576, -0.139115, -0.229508, 0.210698, -0.620434, -0.0887154, -1.42204, -0.0648971, 0.651506, -0.760349, 0.534286, 0.41332, 1.1522, -0.69298, -1.19713, -1.17889, -1.06496, -0.852815, -0.890053, -0.162385, 0.257459, -0.241747, -1.11785, -0.230538, 0.899729, -0.458996, 0.292577, 0.351945, 0.47836, 0.625565, 0.225585, -0.485836, -0.259217, -2.25166, 0.342977, 0.437819, -0.247914, -1.12636, 1.55465, -0.441861, 0.545228, 0.904403, 0.0395662, 1.66672, -0.539633, -0.635173, -0.638768, 0.256603, 1.01104, -1.1674, -0.714249};
	
	int nb_freq = 10;

	for( int i = 0; i < variables.size(); ++i )
	{
		int value = variables[i].get().get_value();
		for( int k = 0; k < nb_freq / 2; ++k )			
		{
			g_x += coeff[ ( i * nb_freq ) + 2*k] * cosine( value, k, MAX_DOMAIN );
			g_x += coeff[ ( i * nb_freq ) + 2*k + 1] * sine( value, k, MAX_DOMAIN );
		}
	}
	
	return std::abs( g_x );
}
#endif

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// Learned cost function with CFN for all-diff 9
#if defined CFN
double AllDiff::required_cost() const
{
	if( alldiff_concept( variables ) )
		return 0.;
	
	constexpr int MAX_COEFF = 100;

	complex<double> g_x{ 0, 0};
	complex<double> coefficient;

// Max ECL - Ctr HO 7.69085
	vector<double> coeff{80, 63, 94, 85, 69, 75, 97, 18, 95, 93, 14, 99, 62, 70, 80, 60, 22, 74, 98, 26, 12, 39, 60, 33, 99, 29, 99, 77, 58, 56, 76, 99, 85, 74, 96, 86, 64, 0, 69, 21, 53, 49, 58, 24, 37, 99, 5, 50, 77, 93, 99, 97, 96, 45, 33, 28, 59, 30, 37, 38, 68, 99, 77, 38, 52, 34, 74, 74, 46, 75, 15, 99, 81, 95, 53, 7, 99, 58, 57, 98, 74, 20, 59, 34, 74, 83, 34, 26, 91, 7};

	int nb_freq = 10;

	for( int i = 0; i < variables.size(); ++i )
	{
		int value = variables[i].get().get_value();
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			coefficient = complex<double>( ( coeff[ ( i * nb_freq ) + 2*k] - ( MAX_COEFF / 2 ) ) / 10, ( coeff[ ( i * nb_freq ) + 2*k + 1] - ( MAX_COEFF / 2 ) ) / 10 );
			g_x += ( coefficient * expo( value, k, MAX_DOMAIN ) );
		}
	}
	
	return std::abs( g_x );
}
#endif

// Learned CPPN cost function with CFN for all-diff 9
#if defined CPPN
double AllDiff::required_cost() const
{
	if( alldiff_concept( variables ) )
		return 0.;

// CPPN  Max ECL - Ctr HO 0.931951
	vector<int> weights{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1};
	weights.insert( weights.end(), {0,1,0,0,0,0,0} );
	
	int LO = ( weights.size() / 7 ) * 10 + 1;

	vector<double> inputs( variables.size() );
	std::transform( variables.begin(), variables.end(), inputs.begin(), [&]( auto v ){ return v.get().get_value(); } );

	vector<double> result( NB_VARS );
	compute( LO, inputs, weights, result );
	int number_units_last_layer = std::count( weights.begin() + 7, weights.begin() + 14, 1 );
		
	return MAX_COST * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( NB_VARS * number_units_last_layer ) );
}
#endif

// old 20.6355
// 68, 45, 64, 6, 20, 52, 95, 46, 80, 23, 17, 61, 81, 65, 71, 2, 76, 30, 32, 46, 32, 19, 19, 28, 65, 32, 40, 30, 40, 12, 21, 81, 27, 94, 98, 33, 49, 10, 86, 52, 28, 44, 91, 0, 72, 10, 46, 26, 18, 15, 4, 72, 58, 60, 52, 31, 46, 47, 48, 89, 44, 36, 95, 80, 33, 90, 94, 29, 77, 6, 14, 57, 58, 43, 90, 25, 42, 25, 94, 87, 77, 51, 19, 8, 57, 96, 11, 7, 7, 51

// Max Outputs 4600
// 73, 68, 26, 80, 77, 33, 24, 30, 84, 80, 46, 50, 54, 42, 11, 38, 14, 97, 57, 69, 73, 37, 12, 29, 58, 39, 52, 91, 34, 78, 59, 7, 81, 96, 69, 14, 27, 48, 90, 4, 53, 91, 38, 12, 70, 61, 46, 81, 29, 76, 1, 55, 17, 21, 73, 61, 73, 79, 66, 28, 77, 1, 43, 71, 68, 97, 82, 68, 52, 16, 40, 81, 3, 18, 34, 94, 71, 16, 4, 0, 71, 13, 68, 70, 11, 97, 76, 35, 7, 79


// old Max ECL - Ctr HO 3.5039
// 89, 28, 0, 18, 92, 16, 28, 0, 94, 19, 96, 68, 57, 99, 58, 93, 91, 21, 76, 92, 76, 26, 73, 0, 24, 7, 45, 56, 45, 51, 50, 89, 17, 8, 38, 0, 16, 64, 23, 74, 2, 24, 18, 47, 66, 26, 4, 22, 51, 7, 54, 89, 26, 99, 41, 27, 78, 75, 43, 29, 60, 21, 20, 9, 24, 9, 3, 22, 43, 57, 1, 24, 75, 12, 5, 35, 14, 72, 76, 24, 94, 3, 30, 16, 42, 17, 17, 70, 7, 62

// Max ECL - Ctr HO 7.69085
//80, 63, 94, 85, 69, 75, 97, 18, 95, 93, 14, 99, 62, 70, 80, 60, 22, 74, 98, 26, 12, 39, 60, 33, 99, 29, 99, 77, 58, 56, 76, 99, 85, 74, 96, 86, 64, 0, 69, 21, 53, 49, 58, 24, 37, 99, 5, 50, 77, 93, 99, 97, 96, 45, 33, 28, 59, 30, 37, 38, 68, 99, 77, 38, 52, 34, 74, 74, 46, 75, 15, 99, 81, 95, 53, 7, 99, 58, 57, 98, 74, 20, 59, 34, 74, 83, 34, 26, 91, 7

// CPPN  Max ECL - Ctr HO 0.931951
// 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1


