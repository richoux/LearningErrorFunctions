#include <cmath>
#include <algorithm>

#include "all-diff.hpp"

// Trigonometric functions
constexpr double PI = std::acos(-1);
constexpr double TWO_PI = 2*PI;

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

// // AllDiff concept as a cost function
// double AllDiff::required_cost() const
// {
// 	// We assume our k variables can take values in [0, k-1]
// 	vector<bool> bitvec( variables.size(), false );

// 	// If we have two variables sharing the same value, return 1 (not a solution)
// 	// otherwise, return 0.
// 	for( int i = 0 ; i < variables.size() ; ++i )
// 		if( !bitvec[ variables[i].get().get_value() ] )
// 			bitvec[ variables[i].get().get_value() ] = true;
// 		else
// 			return 1;
	
// 	return 0;
// }

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// SOFT_ALLDIFF cost function (Petit et al. 2001)
double AllDiff::required_cost() const
{
	double counter = 0;
	
	for( int i = 0 ; i < variables.size() - 1 ; ++i )
		for( int j = i + 1 ; j < variables.size() ; ++j )
			if( variables[i].get().get_value() == variables[j].get().get_value() )
				++counter;

	return counter;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// // Handmade
// double AllDiff::required_cost() const
// {
// 	double counter = 0;
// 	int occurences;
	
// 	for( int i = 0; i < variables[0].get().get_domain_size(); ++i )
// 	{
// 		occurences = std::count_if( variables.begin(), variables.end(), [&](auto v){ return v.get().get_value() == i; } );
// 		if( occurences > 1 )
// 			counter += occurences;
// 	}

// 	return counter;
// }

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

// // Learned cost function for all-diff 9
// double AllDiff::required_cost() const
// {
// 	if( alldiff_concept( variables ) )
// 		return 0.;
	
// 	constexpr int MAX_DOMAIN = 8;

// 	double g_x = 0.;
// 	vector<double> coeff{0.583181, -0.200416, 1.17494, -0.31438, -0.0510316, -0.126238, -0.577367, -0.319095, 0.0890565, -0.180456, -0.15967, -0.471476, 0.0287462, -0.751347, -0.0198749, -1.54704, 0.0971736, 0.0881159, 1.15391, 0.776695, -0.294099, 0.093463, 0.0565593, 0.360842, 0.24014, 0.0677739, -0.199163, -1.36252, 1.06668, -1.9583, -0.161077, 1.51144, -1.49068, 0.504876, -0.240177, -0.71764, -1.50791, -1.4551, -0.474137, -1.15966, 0.583789, -0.453789, 0.178955, 0.463795, 0.858367, 1.04083, -0.112922, -0.353993, -0.594024, -0.631471, -0.97812, -0.654888, -0.0526192, -1.52583, -1.63348, -0.496767, 0.716332, -2.03085, -0.374755, 1.11972, 0.742286, 0.409111, -0.350915, 0.014417, 1.11912, 0.690953, 0.837182, -1.70437, -1.06024, -0.458516, 0.654111, -0.302674, 1.42033, -1.03297, 1.03075, 0.562125, -1.20907, 0.175022, 0.145007, 0.524922, -1.45185, 0.732606, 0.303118, -0.651637, -1.05189, -0.328604, 0.572037, -0.183545, -1.11304, -1.53877};

// 	int nb_freq = 10;

// 	for( int i = 0; i < variables.size(); ++i )
// 	{
// 		int value = variables[i].get().get_value();
// 		for( int k = 0; k < nb_freq / 2; ++k )
// 		{
// 			g_x += coeff[ ( i * nb_freq ) + 2*k] * cosine( value, k, MAX_DOMAIN );
// 			g_x += coeff[ ( i * nb_freq ) + 2*k + 1] * sine( value, k, MAX_DOMAIN );
// 		}
// 	}
	
// 	return std::abs( g_x );
// }


