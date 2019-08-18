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

double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int max_domain )
{
	double g_x = 0.;
	
	int nb_freq = coeff.size() / vars.size();

	for( int i = 0; i < var.size(); ++i )
	{
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			g_x += coeff[ ( i * nb_freq ) + 2*k ].get().get_value() * cosine( var[i], k, max_domain );
			g_x += coeff[ ( i * nb_freq ) + 2*k + 1 ].get().get_value() * sine( var[i], k, max_domain );
		}
	}
	
	return std::abs( g_x );	
}
