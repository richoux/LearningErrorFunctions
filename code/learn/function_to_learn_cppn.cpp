#include <cmath>
#include <complex>
#include <algorithm>
#include <numeric>
#include <limits>

// #include <iostream>
// #include <iterator>

#include "function_to_learn_cppn.hpp"

void interpreter_transformation( const int& number,
                                 const vector<double>& inputs,
                                 const vector<double>& params,
                                 const int& start_index_output,
                                 vector<double>& outputs )
{
	// cout << "\nTransfo number: " << number << "\nTransfo inputs: ";
	// std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );
	
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() + start_index_output );
		break;
		// number of elements on the right equals to y
	case 1:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the right smaller than or equals to y
	case 2:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] <= inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the right greater than or equals to y
	case 3:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] >= inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements smaller than or equals to y + param
	case 4:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] <= inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements greater than or equals to y + param
	case 5:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] >= inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
		// max(0, param - y)
	case 6:
		for( int y = 0; y < (int)inputs.size(); ++y )
			outputs[y + start_index_output] = std::max( 0.0, params[y] - inputs[y] );
		break;
		// max(0, x_i - x_i+1 )
	case 7:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			outputs[y + start_index_output] = std::max( 0.0, inputs[y] - inputs[y+1] );
		break;
	}

	// cout << "\nTransfo ouputs: ";
	// std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
}

void interpreter_arithmetic( const int& number,
                             const vector<double>& inputs,
                             const int& size,
                             vector<double>& outputs )
{
	// cout << "\nArith number: " << number << "\nArith inputs: ";
	// std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );

	std::copy_n( inputs.begin(), size, outputs.begin() );
	
	// addition
	if( number == 0 )
	{
		for( int i = size; i < (int)inputs.size(); ++i )
			outputs[ i % size ] += inputs[i];
	}
	// multiplication
	else
	{
		for( int i = size; i < (int)inputs.size(); ++i )
			outputs[ i % size ] *= inputs[i];
	}

	// cout << "\nArith ouputs: ";
	// std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
}
	
double interpreter_agregation( const int& number,
                               const vector<double>& inputs )
{
	// cout << "\nAgreg number: " << number << "\nAgreg inputs: ";
	// std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );

	if( number == 0 )
		return std::count_if( inputs.begin(), inputs.end(), [](const auto& i){ return i > 0; } );
	else
		return std::accumulate( inputs.begin(), inputs.end(), 0.0 );
}

double interpreter_comparison( const int& number,
                               const double& input,
                               const double& param )
{
	// cout << "\nCompar number: " << number << "\nCompar inputs: " << input << "\n";

	switch( number )
	{
		// Identity
	case 0:
		return input;
		break;
		// input equals to parameter
	case 1:
		return std::abs( input - param );
		break;
		// input greater than or equals to parameter
	case 2:
		return std::max( 0.0, param - input );
		break;
		// input less than or equals to parameter
	case 3:
		return std::max( 0.0, input - param );
		break;
	}
}

vector<double> layer_transformation( const vector<double>& inputs,
                                     int nb_vars,
                                     const vector<double>& params,
                                     const vector<int>& weights )
{
	//precondition: we should have at least one 1 in weights.
	
	int number_active_units = std::count( weights.begin(), weights.begin() + number_units_transfo, 1 );
	vector<double> outputs( number_active_units * nb_vars, 0.0 );
	int index_active_unit = 0;
	
	for( int i = 0; i < number_units_transfo; ++i )
		if( weights[i] == 1 )
		{
			int start_index = index_active_unit * nb_vars;
			++index_active_unit;
			interpreter_transformation( i, inputs, params, start_index, outputs );
		}

	return outputs;
}

vector<double> layer_arithmetic( const vector<double>& inputs,
                                 int nb_vars,
                                 const int& weight )
{
	vector<double> outputs( nb_vars, 0.0 );
	interpreter_arithmetic( weight, inputs, nb_vars, outputs );

	return outputs;
}

double layer_agregation( const vector<double>& inputs,
                         const int& weight )
{
	return interpreter_agregation( weight, inputs );
}

double layer_comparison( const double& input,
                         const vector<int>& weights,
                         const double& param )
{
	//precondition: we should have exactly one 1 in weights.
	
	for( int i = 0; i < number_units_compar; ++i )
		if( weights[ i + number_units_transfo + 2 ] == 1 )
			return interpreter_comparison( i, input, param );

	// should never happen
	return -1;
}

double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& nb_vars )
{
	// heavy penalty for having 0 active transformation weights or not exactly 1 active comparison weight
	if( std::count( weights.begin(), weights.begin() + number_units_transfo, 1 ) == 0
	    ||
	    std::count( std::prev( weights.end(), number_units_compar ), weights.end(), 1 ) != 1 )
		return std::numeric_limits<double>::max();

	// transformation layer
	//        |
	//        v
	// arithmetic layer
	//        |
	//        v
	// agregation layer
	//        |
	//        v
	// comparison layer

	auto output_transfo = layer_transformation( inputs, nb_vars, params, weights );
	auto output_arith = layer_arithmetic( output_transfo, nb_vars, weights[ number_units_transfo ] );
	auto output_agreg = layer_agregation( output_arith, weights[ number_units_transfo + 1 ] );

	// auto plop = layer_comparison( output_agreg, weights, params[0] );
	// cout << "Network output: " << plop << "\n";
	// return plop;
  return layer_comparison( output_agreg, weights, params[0] );
}

// Variable version
double g( const vector< Variable >& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int start,
          int nb_vars )
{
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() );
	
	std::copy( vars.begin() + start, vars.begin() + start + nb_vars, inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get_value(); } );

	return intermediate_g( inputs, params, weights_int, nb_vars );
}

// Int vector version
double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<double>& vars,
          int start,
          int end )
{
	return intermediate_g( vars, params, weights, end - start );
}

// Int vector with int config version
double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int start,
          int nb_vars )

{
	vector<double> inputs( nb_vars );
	std::copy( vars.begin() + start, vars.begin() + start + nb_vars, inputs.begin() );

	return intermediate_g( inputs, params, weights, nb_vars );
}
