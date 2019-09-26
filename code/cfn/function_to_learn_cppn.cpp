#include <cmath>
#include <complex>
#include <algorithm>

#if defined CHRONO
#include <chrono>
#endif

#include "function_to_learn_cppn.hpp"

#if defined CHRONO
static bool first = true;
#endif

// Trigonometric functions
//constexpr double PI = std::acos(-1);
constexpr double PI = M_PI;
constexpr double TWO_PI = 2*PI;

inline double sigmoid( double x ) { return 1. / ( 1 + std::exp( -x ) ); }
inline double cubic_tanh( double x ) { return std::tanh( std::pow( x, 3 ) ); }
inline double gaussian( double x ) { return std::exp( std::pow( x, 2 ) ) * 2 - 1; }

vector<double> interpreter( int number, const vector<double>& inputs )
{
	vector<double> outputs( inputs.size() );
	
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() );
		break;
		// Sigmoid
	case 1:
		transform( inputs.begin(), inputs.end(), outputs.begin(), sigmoid );
		break;
		// Tanh
	case 2:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::tanh(x); } );
		break;
		// Cubic Tanh
	case 3:
		transform( inputs.begin(), inputs.end(), outputs.begin(), cubic_tanh );
		break;
		// Gaussian
	case 4:
		transform( inputs.begin(), inputs.end(), outputs.begin(), gaussian );
		break;
		// Sine
	case 5:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::sin(x); } );
		break;
		// Absolute value = case 6
	Default:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::abs(x); } );
	}

	return outputs;
}


// Flat vector version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int start, int end, int var_max_value )
{
#if defined CHRONO
	auto start_clock = std::chrono::steady_clock::now();
#endif

	vector<double> inputs( vars.size() );
	copy( vars.begin(), vars.end(), inputs.begin() );
	double g_x = 0.;
	
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
