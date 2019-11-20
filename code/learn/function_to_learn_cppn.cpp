#include <cmath>
#include <complex>
#include <algorithm>

// #include <iostream>

#include "function_to_learn_cppn.hpp"

inline double sigmoid( const double& x ) { return 1. / ( 1 + std::exp( -x ) ); }

double inside( double value, double lower, double upper )
{
	if( value >= lower )
	{
		if( value <= upper )
			return 0.0;
		else
			return value - upper;
	}
	else
		return lower - value;
}

double outside( double value, double lower, double upper )
{
	if( value < lower || value > upper )
		return 0.0;
	else
		return std::min( value - lower, upper - value ) + 1; // +1 to avoid returning 0 if value == lower or value == upper
}

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

void interpreter_transformation( int number, const vector<double>& inputs, vector<double>& outputs )
{
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() );
		break;
		// Equals to
	case 1:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::count( inputs.begin(), inputs.end(), y ); } );
		break;
		// Less then
	case 2:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::count_if( inputs.begin(), inputs.end(), [&y](const auto& x){ return x < y; } ); } );
		break;
		// Greater than
	case 3:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::count_if( inputs.begin(), inputs.end(), [&y](const auto& x){ return x > y; } ); } );
		break;
		// Different
	case 4:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::count_if( inputs.begin(), inputs.end(), [&y](const auto& x){ return x != y; } ); } );
		break;
		// Equals to, left elements
	case 5:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y];
		break;
		// Less than, left elements
	case 6:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y];
		break;
		// Greater than, left elements
	case 7:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y];
		break;
		// Equals to, right elements
	case 8:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y];
		break;
		// Less than, right elements
	case 9:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y];
		break;
		// Greater than, right elements
	case 10:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y];
		break;
		// Continuous box of values
	case 11:
		int y = 0;
		while( y < (int)inputs.size() )
		{
			int count = 1;
			int x = y + 1;
			while( inputs[y] == inputs[x] && x < (int)inputs.size() )
			{
				++count;
				++x;
			}

			std::fill_n( outputs.begin() + y, count, count );
			y += count;
		}
		break;
	}
}

void interpreter_comparison( int number, const vector<double>& inputs, vector<double>& outputs, double parameter_1, double parameter_2 )
{
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() );
		break;
		// Equals to parameter
	case 1:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::abs( parameter_1 - y ); } );
		break;
		// Greater than parameter
	case 2:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::max( 0.0, parameter_1 - y ); } );
		break;
		// Less than parameter
	case 3:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return std::max( 0.0, y - parameter_1 ); } );
		break;
		// Inside [p1,p2]
	case 4:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return inside( y, parameter_1, parameter_2); } );
		break;
		// Outside [p1,p2]
	case 5:
		transform( inputs.begin(), inputs.end(), outputs.begin(), [](const auto& y) -> double { return outside( y, parameter_1, parameter_2); } );
		break;
	}
}

vector<double> transformation_layer( const vector<double>& inputs, const vector<int>& weights )
{
	
}

vector<double> comparison_layer( const vector<double>& inputs, const vector<int>& weights )
{
	
}


void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& result, int max )
{
	int L = LO / 10;
	int O = LO % 10;

	// DEBUG
	// cout << "input: ";
	// std::copy( inputs.begin(),
	//            inputs.end(),
	//            ostream_iterator<double>( cout, " " ) );
	// cout << "\n";
	
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
	// cout << "result: ";
	// std::copy( result.begin(),
	//            result.end(),
	//            ostream_iterator<double>( cout, " " ) );
	// cout << "\n";
}

double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int max )
{
	double max_cost = nb_vars + 0.9;

	// transformation layer
	//        |
	//        v
	// comparison layer
	//        |
	//        v
	//     sigmoid
	//        |
	//        v
	//  normalized sum

	// !!! we can have several result vectors after each layer !!!
	auto result = transformation_layer( inputs, weights );
	result = comparison_layer( result, weights );
	std::transform( result.begin(), result.end(), result.begin(), [](const auto& x){ return sigmoid( x ); } );
	double normalized_sum = std::accumulate( result.begin(), result.end(), 0.0 ) / (int)result.size();

	// DEBUG
	// cout << "cost: " << max_cost * ( std::accumulate( result.begin(), result.end(), 0.0 ) / ( nb_vars * number_units_last_layer ) ) << "\n\n";
		
	return max_cost * normalized_sum;
}

// ref_wrapper<Variable> version
double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int max )
{
	int nb_vars = (int)vars.size();
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() + number_functions );
	std::copy( vars.begin(), vars.end(), inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get().get_value(); } );
	
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

	return intermediate_g( weights_int, inputs, nb_vars, max );
}

// Int vector version
double g( const vector< int >& weights, const vector<double>& vars, int start, int end, int max )
{
	return intermediate_g( weights, vars, end - start, max );
}
