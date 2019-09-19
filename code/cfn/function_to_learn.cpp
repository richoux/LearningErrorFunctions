#include <cmath>
#include <complex>

#if defined CHRONO
#include <chrono>
#endif

#include "function_to_learn.hpp"

#if defined CHRONO
static bool first = true;
#endif

// Trigonometric functions
//constexpr double PI = std::acos(-1);
constexpr double PI = M_PI;
constexpr double TWO_PI = 2*PI;

double sine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 1.;
	else
		return sin( TWO_PI*k*x / ( max + 1 ) );
}

double cosine( double x, unsigned int k, int max )
{
	if( k == 0 || x == 0. )
		return 0.;
	else
		return cos( TWO_PI*k*x / ( max + 1 ) );
}

inline complex<double> expo( double x, unsigned int k, int max )
{
	return complex<double>( cosine( x, k, max ), sine( x, k, max ) );
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
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif

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

#if defined CHRONO
	if( first )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "g: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first = false;
	}
#endif

	return std::abs( g_x );	
}

// Flat vector version
double g( const vector< reference_wrapper<Variable> >& coeff, const vector<int>& vars, int start, int end, int var_max_value )
{
#if defined CHRONO
	auto start_clock = std::chrono::steady_clock::now();
#endif

	complex<double> g_x{ 0, 0};
	complex<double> coefficient;
	
	int nb_freq = coeff.size() / ( end - start );
	int offset = coeff[0].get().get_domain_size() / 2;
	
	for( int i = start; i < end; ++i )
	{
		for( int k = 0; k < nb_freq / 2; ++k )
		{
			coefficient = complex<double>( static_cast<double>( coeff[ ( ( i - start ) * nb_freq ) + 2*k].get().get_value() - offset ) / 10,
			                               static_cast<double>( coeff[ ( ( i - start ) * nb_freq ) + 2*k + 1].get().get_value() - offset ) / 10 );
			g_x += ( coefficient * expo( vars[i], k, var_max_value ) );
		}
	}

#if defined CHRONO
	if( first )
	{
		auto end_clock = std::chrono::steady_clock::now();
		cerr << "g: " << std::chrono::duration_cast<std::chrono::microseconds>(end_clock - start_clock).count() << "µs\n";
		first = false;
	}
#endif

	return std::abs( g_x );	
}
