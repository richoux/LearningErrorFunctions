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

// ref_wrapper<Variable> version
double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int var_max_value )
{
	vector< Variable > coefficients;
	std::transform( coeff.begin(), coeff.end(), std::back_inserter( coefficients ), []( auto& c ){ return c.get(); } );
	
	return g( coefficients, vars, var_max_value );
}

// Variable version
double g( const vector< Variable >& coeff, const vector<int>& vars, int var_max_value )
{
	double g_x = 0.;
	
	int nb_freq = coeff.size() / vars.size();
	int offset = coeff[0].get_domain_size() / 2;
	
	for( int i = 0; i < vars.size(); ++i )
	{
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			g_x += ( static_cast<double>( coeff[ ( i * nb_freq ) + 2*k ].get_value() - offset ) / 10 ) * cosine( vars[i], k, var_max_value );
			g_x += ( static_cast<double>( coeff[ ( i * nb_freq ) + 2*k + 1 ].get_value() - offset ) / 10 ) * sine( vars[i], k, var_max_value );
		}
	}
	
	return std::abs( g_x );	
}
