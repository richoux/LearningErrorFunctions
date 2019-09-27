#include <cmath>
#include <complex>
#include <algorithm>

#if defined CHRONO
#include <chrono>
#endif

#include "function_to_learn_cppn.hpp"

#if defined CHRONO or DEBUG
static bool first = true;
#endif

// Trigonometric functions
//constexpr double PI = std::acos(-1);
constexpr double PI = M_PI;
constexpr double TWO_PI = 2*PI;

inline double cubic_tanh( double x ) { return std::tanh( std::pow( x, 3 ) ); }
inline double sigmoid( double x ) { return 1. / ( 1 + std::exp( -x ) ); }
inline double gaussian( double x ) { return std::exp( - std::pow( x, 2 ) ) * 2 - 1; }

vector<double> interpreter( int number, const vector<double>& inputs )
{
	vector<double> outputs( inputs.size() );
	
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() );
		break;
		// Absolute value
	case 1:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::abs(x); } );
		break;
		// Sine
	case 2:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::sin(x); } );
		break;
		// Tanh
	case 3:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::tanh(x); } );
		break;
		// Cubic Tanh
	case 4:
		transform( inputs.begin(), inputs.end(), outputs.begin(), cubic_tanh );
		break;
		// Sigmoid
	case 5:
		transform( inputs.begin(), inputs.end(), outputs.begin(), sigmoid );
		break;
		// Gaussian
	case 6:
		transform( inputs.begin(), inputs.end(), outputs.begin(), gaussian );
		break;
	}

	return outputs;
}

void parse( int LO, int& L, int& O )
{
	L = LO / 10;
	O = LO % 10;
}

vector<double> compute( int LO, const vector<double>& inputs, const vector<int>& weights )
{
	int L, O;
	parse( LO, L, O );

	if( weights[ ( L - 1 ) * 7 + O ] != 1 )
		return vector<double>( inputs.size(), 0.0 );
	else
	{	
		vector<double> temp_inputs( inputs );
		vector<double> temp_outputs( inputs.size() );
		vector<double> temp_result;
		
		for( int l = 1; l < L; ++l )
		{			
			std::fill( temp_outputs.begin(), temp_outputs.end(), 0.0 );
			for( int i = 0; i <= 6; ++i )
			{
				if( weights[ ( l - 1 ) * 7 + i ] == 1 )
				{
					temp_result = interpreter( i, temp_inputs );
					for( int j = 0; j < (int)inputs.size(); ++j )
						temp_outputs[j] += temp_result[j];
				}
			}
			std::copy( temp_outputs.begin(), temp_outputs.end(), temp_inputs.begin() );
		}
		
		return interpreter( O, temp_inputs );
	}
}

double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int var_max_value )
{
#if defined CHRONO
	auto start_clock = std::chrono::steady_clock::now();
#endif
	int LO = ( weights.size() / 7 ) * 10;
	
	auto result = compute( LO, inputs, weights );
	int number_units_last_layer = std::count( weights.begin() + 7, weights.begin() + 14, 1 );
	
	double max_cost = nb_vars + ( var_max_value / ( std::pow( 10, std::floor( std::log10( var_max_value ) ) + 1 ) ) );
#if defined DEBUG
	if( first )
	{
		cerr << "LO: " << LO << "\n"
		     << "number_units_last_layer: " << number_units_last_layer << "\n";
		cerr << "Weights: ";

		for( auto w : weights )
			cerr << w << " ";
		
		cerr << "\nIntermediate result: ";

		for( auto r : result )
			cerr << r << " ";
				
		cerr << "\nMax cost: " << max_cost << "\n"
		     << "g = " << max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) ) << "\n";
	}
#endif
	
#if defined CHRONO
	if( first )
	{
		auto end_clock = std::chrono::steady_clock::now();
		cerr << "g: " << std::chrono::duration_cast<std::chrono::microseconds>(end_clock - start_clock).count() << "µs\n";
	}
#endif

#if defined CHRONO or DEBUG
	first = false;
#endif
	
	return max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) );
}

// ref_wrapper<Variable> version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int var_max_value )
{
	int nb_vars = (int)vars.size();
	vector<double> inputs( vars.size() );
	vector<int> weights_int( weights.size() + 7 );
	std::copy( vars.begin(), vars.end(), inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), [&]( auto w ){ return w.get().get_value(); } );
	weights_int[ weights.size() ] = 1;
	std::fill( weights_int.begin() + weights.size() + 1, weights_int.end(), 0 );

	return intermediate_g( weights_int, inputs, nb_vars, var_max_value );
}

// Variable version
double g( const vector< Variable >& weights, const vector<int>& vars, int var_max_value )
{
	int nb_vars = (int)vars.size();
	vector<double> inputs( vars.size() );
	vector<int> weights_int( weights.size() + 7 );
	std::copy( vars.begin(), vars.end(), inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), [&]( auto w ){ return w.get_value(); } );
	weights_int[ weights.size() ] = 1;
	std::fill( weights_int.begin() + weights.size() + 1, weights_int.end(), 0 );

	return intermediate_g( weights_int, inputs, nb_vars, var_max_value );
}

// Flat vector version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int start, int end, int var_max_value )
{
	int nb_vars = end - start;
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() + 7 );
	std::copy( vars.begin() + start, vars.begin() + start + end, inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), [&]( auto w ){ return w.get().get_value(); } );
	weights_int[ weights.size() ] = 1;
	std::fill( weights_int.begin() + weights.size() + 1, weights_int.end(), 0 );

	return intermediate_g( weights_int, inputs, nb_vars, var_max_value );
}
