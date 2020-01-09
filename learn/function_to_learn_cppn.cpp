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
#if defined DEBUG
	cout << "\nTransfo number: " << number << "\nTransfo inputs: ";
	std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );
#endif
	
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
		// number of elements on the right smaller than y
	case 2:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the right greater than y
	case 3:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the left equals to y
	case 4:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the left smaller than y
	case 5:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements on the left greater than y
	case 6:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements equals to y + param
	case 7:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] == inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements smaller than y + param
	case 8:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] < inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements greater than y + param
	case 9:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] > inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
		// max(0, y - param)
	case 10:
		for( int y = 0; y < (int)inputs.size(); ++y )
			outputs[y + start_index_output] = std::max( 0.0, inputs[y] - params[y] );
		break;
		// max(0, param - y)
	case 11:
		for( int y = 0; y < (int)inputs.size(); ++y )
			outputs[y + start_index_output] = std::max( 0.0, params[y] - inputs[y] );
		break;
		// max(0, x_i - x_i+1 )
	case 12:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			outputs[y + start_index_output] = std::max( 0.0, inputs[y] - inputs[y+1] );
		break;
		// max(0, x_i+1 - x_i )
	case 13:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			outputs[y + start_index_output] = std::max( 0.0, inputs[y+1] - inputs[y] );
		break;
		// number of elements equals to y
	case 14:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] == inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements greater than y
	case 15:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] > inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements smaller than y
	case 16:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] < inputs[y] )
					++outputs[y + start_index_output];
		break;
		// number of elements greater than or equals to y AND less than or equals to y + param 
	case 17:
		for( int y = 0; y < (int)inputs.size(); ++y )
			for( int x = 0; x < (int)inputs.size(); ++x )
				if( x != y && inputs[x] >= inputs[y] && inputs[x] <= inputs[y] + params[y] )
					++outputs[y + start_index_output];
		break;
	}

#if defined DEBUG
	cout << "\nTransfo ouputs: ";
	std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
#endif
}

void interpreter_arithmetic( const int& number,
                             const vector<double>& inputs,
                             const int& size,
                             vector<double>& outputs )
{
#if defined DEBUG
	cout << "\nArith number: " << number << "\nArith inputs: ";
	std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );
#endif
	
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

#if defined DEBUG
	cout << "\nArith ouputs: ";
	std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
#endif
}
	
double interpreter_aggregation( const int& number,
                               const vector<double>& inputs )
{
#if defined DEBUG
	cout << "\nAggreg number: " << number << "\nAggreg inputs: ";
	std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );
#endif
	
	if( number == 0 )
		return std::count_if( inputs.begin(), inputs.end(), [](const auto& i){ return i > 0; } );
	else
		return std::accumulate( inputs.begin(), inputs.end(), 0.0 );
}

double interpreter_comparison( const int& number,
                               const double& input,
                               const int& max_domain_value,
                               const int& nb_vars,
                               const double& param )
{
#if defined DEBUG
	cout << "\nCompar number: " << number << "\nCompar inputs: " << input << "\n";
#endif
	
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
		// Euclidian division of the difference between input and parameter by the domain size
	case 4:
		if( input - param == 0.0 )
			return 0.0;
		else
			return 1 + ( static_cast<int>( std::abs( input - param ) ) / max_domain_value );
		break;
		// Euclidian division of the input by the domain size
	case 5:
		if( input == 0.0 )
			return 0.0;
		else
			return 1 + ( static_cast<int>( input ) / max_domain_value );
		break;
		// input equals to the number of variables
	case 6:		
		return std::abs( input - nb_vars );
		break;
		// input greater than or equals to the number of variables
	case 7:
		return std::max( 0.0, nb_vars - input );
		break;
		// input less than or equals to the number of variables
	case 8:
		return std::max( 0.0, input - nb_vars );
		break;
	}

	// should never happen
	return -1.0;
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

double layer_aggregation( const vector<double>& inputs,
                         const int& weight )
{
	return interpreter_aggregation( weight, inputs );
}

double layer_comparison( const double& input,
                         const vector<int>& weights,
                         const int& max_domain_value,
                         const int& nb_vars,
                         const double& param )
{
	//precondition: we should have exactly one 1 in weights.
	
	for( int i = 0; i < number_units_compar; ++i )
		if( weights[ i + number_units_transfo + 2 ] == 1 )
			return interpreter_comparison( i, input, max_domain_value, nb_vars, param );

	// should never happen
	return -1;
}

double intermediate_g( const vector<double>& inputs,
                       const vector<double>& params,
                       const vector<int>& weights,
                       const int& max_domain_value,
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
	// aggregation layer
	//        |
	//        v
	// comparison layer

	auto output_transfo = layer_transformation( inputs, nb_vars, params, weights );
	auto output_arith = layer_arithmetic( output_transfo, nb_vars, weights[ number_units_transfo ] );
	auto output_aggreg = layer_aggregation( output_arith, weights[ number_units_transfo + 1 ] );

#if defined DEBUG
	auto test = layer_comparison( output_aggreg, weights, max_domain_value, nb_vars, params[0] );
	cout << "Network output: " << test << "\n";
	return test;
#else
	return layer_comparison( output_aggreg, weights, max_domain_value, nb_vars, params[0] );
#endif
}

// Variable version
double g( const vector< Variable >& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int max_domain_value,
          int start,
          int nb_vars )
{
	vector<double> inputs( nb_vars );
	vector<int> weights_int( weights.size() );
	
	std::copy( vars.begin() + start, vars.begin() + start + nb_vars, inputs.begin() );
	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get_value(); } );

	return intermediate_g( inputs, params, weights_int, max_domain_value, nb_vars );
}

// Int vector version
double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<double>& vars,
          int max_domain_value,
          int start,
          int end )
{
	return intermediate_g( vars, params, weights, max_domain_value, end - start );
}

// Int vector with int config version
double g( const vector<int>& weights,
          const vector<double>& params,
          const vector<int>& vars,
          int max_domain_value,
          int start,
          int nb_vars )

{
	vector<double> inputs( nb_vars );
	std::copy( vars.begin() + start, vars.begin() + start + nb_vars, inputs.begin() );

	return intermediate_g( inputs, params, weights, max_domain_value, nb_vars );
}
