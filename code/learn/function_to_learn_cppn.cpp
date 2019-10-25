#include <cmath>
#include <complex>
#include <algorithm>

#include <iostream>

#include "function_to_learn_cppn.hpp"

inline double cubic_tanh( double x ) { return std::tanh( std::pow( x, 3 ) ); }
inline double sigmoid( double x ) { return 1. / ( 1 + std::exp( -x ) ); }
inline double gaussian( double x ) { return std::exp( -8 * std::pow( x , 2 ) ); }

// Are we normalizing integer values from [0, max_value] or real values?
bool integer_only( const vector<double>& vec )
{
	double intpart;
	for( auto& v : vec )
		if( std::modf( v, &intpart ) != 0.0 )
			return false;

	return true;
}

void norm_0_1( const vector<double>& vec, vector<double>& normalized, int max_value )
{
	if( integer_only( vec ) )
		transform( vec.begin(),
		           vec.end(),
		           normalized.begin(),
		           [&max_value](auto x) -> double { return x / max_value; } );
	else
	{
		auto min = std::min_element( vec.begin(), vec.end() );
		auto max = std::max_element( vec.begin(), vec.end() );

		if( min == max )
			fill( normalized.begin(), normalized.end(), 0.5 );
		else		
			transform( vec.begin(),
			           vec.end(),
			           normalized.begin(),
			           [&min,&max](auto x) -> double { return (x - *min) / (*max - *min); } );
	}
}

void norm_minus1_1( const vector<double>& vec, vector<double>& normalized, int max_value )
{
	if( integer_only( vec ) )
		transform( vec.begin(),
		           vec.end(),
		           normalized.begin(),
		           [&max_value](auto x) -> double { return 2*x / max_value - 1; } );
	else
	{
		auto min = std::min_element( vec.begin(), vec.end() );
		auto max = std::max_element( vec.begin(), vec.end() );
		
		if( min == max )
			fill( normalized.begin(), normalized.end(), 0.5 );
		else		
			transform( vec.begin(),
			           vec.end(),
			           normalized.begin(),
			           [&min,&max](auto x) -> double { return 2*(x - *min) / (*max - *min) - 1; } );
	}
}

void interpreter( int number, const vector<double>& inputs, vector<double>& outputs, int max )
{
	switch( number )
	{
	// 	// Identity
	// case 0:
	// 	copy( inputs.begin(), inputs.end(), outputs.begin() );
	// 	break;
	// 	// Absolute value
	// case 1:
	// 	transform( inputs.begin(), inputs.end(), outputs.begin(), [](auto x) -> double { return std::abs(x); } );
	// 	break;

		// Normalization 0_1
	case 0:
		norm_0_1( inputs, outputs, max );
		break;
		// Normalization -1_1
	case 1:
		norm_minus1_1( inputs, outputs, max );
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
	// 	// Normalization
	// case 7:
	// 	normalization( inputs, outputs );
	// 	break;
	}
}

void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& result, int max )
{
	int L = LO / 10;
	int O = LO % 10;

	// DEBUG
	cout << "input: ";
	std::copy( inputs.begin(),
	           inputs.end(),
	           ostream_iterator<double>( cout, " " ) );
	cout << "\n";
	
	auto inputs_size = inputs.size();
	
	vector<double> temp_inputs( inputs_size );
	vector<double> temp_outputs( inputs_size );
	vector<double> temp_result( inputs_size );

	if( weights[ ( L - 1 ) * number_functions + O ] != 1 )
		std::fill( result.begin(), result.end(), 0.0 );
	else
	{
		std::copy( inputs.begin(), inputs.end(), temp_inputs.begin() );
		
		for( int l = 1; l < L; ++l )
		{			
			std::fill( temp_outputs.begin(), temp_outputs.end(), 0.0 );
			for( int i = 0; i < number_functions; ++i )
			{
				if( weights[ ( l - 1 ) * number_functions + i ] == 1 )
				{
					interpreter( i, temp_inputs, temp_result, max );
					for( int j = 0; j < (int)inputs.size(); ++j )
						temp_outputs[j] += temp_result[j];
				}
			}
			std::copy( temp_outputs.begin(), temp_outputs.end(), temp_inputs.begin() );
		}

		interpreter( O, temp_inputs, result, max );
	}

	// DEBUG
	cout << "result: ";
	std::copy( result.begin(),
	           result.end(),
	           ostream_iterator<double>( cout, " " ) );
	cout << "\n";
}

double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int max )
{
	int LO = ( weights.size() / number_functions ) * 10;// + ( number_functions - 1 );
	vector<double> result( nb_vars ); //inputs.size() );
	int number_units_last_layer = std::count( weights.begin() + number_functions, weights.begin() + 2*number_functions, 1 );
	double max_cost = nb_vars + 0.9;
	
	compute( LO, inputs, weights, result, max );

	// DEBUG
	cout << "cost: " << max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) ) << "\n\n";
		
	// max_cost times the sigmoid of the mean of the values in result
	//return max_cost * sigmoid( std::accumulate( result.begin(), result.end(), 0.0 ) / nb_vars );
	return max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) );
}

// ref_wrapper<Variable> version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int max )
{
	int nb_vars = (int)vars.size();
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() + number_functions );
	std::copy( vars.begin(), vars.end(), inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get().get_value(); } );
	
	// Last layer: identity
	std::fill( weights_int.begin() + weights.size(), weights_int.end(), 0 );
	weights_int[ weights.size() ] = 1;

	return intermediate_g( weights_int, inputs, nb_vars, max );
}

// Variable version
double g( const vector< Variable >& weights, const vector<int>& vars, int max )
{
	int nb_vars = (int)vars.size();
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() + number_functions );
	std::copy( vars.begin(), vars.end(), inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get_value(); } );

	// Last layer: identity
	std::fill( weights_int.begin() + weights.size(), weights_int.end(), 0 );
	weights_int[ weights.size() ] = 1;

	return intermediate_g( weights_int, inputs, nb_vars, max );
}

// Flat vector version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int start, int end, int max )
{
	int nb_vars = end - start;
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() + number_functions );
	std::copy( vars.begin() + start, vars.begin() + start + end, inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get().get_value(); } );

	// Last layer: identity
	std::fill( weights_int.begin() + weights.size(), weights_int.end(), 0 );
	weights_int[ weights.size() ] = 1;

	return intermediate_g( weights_int, inputs, nb_vars, max );
}

// Int vector version
double g( const vector< int >& weights, const vector<double>& vars, int start, int end, int max )
{
	return intermediate_g( weights, vars, end - start, max );
}
