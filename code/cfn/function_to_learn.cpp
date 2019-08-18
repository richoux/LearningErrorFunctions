#include <cmath>

#include "function_to_learn.hpp"

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

// Hacky, to fix: we should have just one version

// ref_wrapper<Variable> version
double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int max_domain )
{
	double g_x = 0.;
	
	int nb_freq = coeff.size() / vars.size();
	int offset = coeff[0].get().get_domain_size() / 2;
	
	for( int i = 0; i < vars.size(); ++i )
	{
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			g_x += ( coeff[ ( i * nb_freq ) + 2*k ].get().get_value() - offset ) * cosine( vars[i], k, max_domain );
			g_x += ( coeff[ ( i * nb_freq ) + 2*k + 1 ].get().get_value() - offset ) * sine( vars[i], k, max_domain );
		}
	}
	
	return std::abs( g_x );	
}

// Variable version
double g( const vector< Variable >& coeff, const vector<int>& vars, int max_domain )
{
	double g_x = 0.;
	
	int nb_freq = coeff.size() / vars.size();
	int offset = coeff[0].get_domain_size() / 2;
	
	for( int i = 0; i < vars.size(); ++i )
	{
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			g_x += ( coeff[ ( i * nb_freq ) + 2*k ].get_value() - offset ) * cosine( vars[i], k, max_domain );
			g_x += ( coeff[ ( i * nb_freq ) + 2*k + 1 ].get_value() - offset ) * sine( vars[i], k, max_domain );
		}
	}
	
	return std::abs( g_x );	
}
