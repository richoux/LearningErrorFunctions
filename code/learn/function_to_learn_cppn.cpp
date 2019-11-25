#include <cmath>
#include <complex>
#include <algorithm>
#include <numeric>

// #include <iostream>
// #include <iterator>

#include "function_to_learn_cppn.hpp"

double sigmoid( const double& x, const int& size )
{
	if( x < 0.0005 )
		return 0.0;
	else
	// 	if( x > 0.95 )
	// 		return 1.0;
	// 	else
		return 1. / ( 1 + std::exp( - ( x - size/2 ) ) );
}

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

void interpreter_transformation( int number,
                                 const vector<double>& inputs,
                                 vector<double>& outputs )
{
	int start_index_output = number * (int)inputs.size();

	// cout << "\nTransfo number: " << number << "\nTransfo inputs: ";
	// std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );
	
	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() + start_index_output );
		break;
		// Equals to
	case 1:
		std::transform( inputs.begin(),
		                inputs.end(),
		                outputs.begin() + start_index_output,
		                [&inputs](const auto& y) -> double { return std::count( inputs.begin(), inputs.end(), y ); } );
		break;
		// Less then
	case 2:
		std::transform( inputs.begin(),
		                inputs.end(),
		                outputs.begin() + start_index_output,
		                [&inputs](const auto& y) -> double
		                {
			                return std::count_if( inputs.begin(),
			                                      inputs.end(),
			                                      [&y](const auto& x){ return x < y; } );
		                } );
		break;
		// Greater than
	case 3:
		std::transform( inputs.begin(),
		                inputs.end(),
		                outputs.begin() + start_index_output,
		                [&inputs](const auto& y) -> double
		                { return std::count_if( inputs.begin(),
		                                        inputs.end(),
		                                        [&y](const auto& x){ return x > y; } );
		                } );
		break;
		// Different
	case 4:
		std::transform( inputs.begin(),
		                inputs.end(),
		                outputs.begin() + start_index_output,
		                [&inputs](const auto& y) -> double
		                { return std::count_if( inputs.begin(),
		                                        inputs.end(),
		                                        [&y](const auto& x){ return x != y; } );
		                } );
		break;
		// Equals to, left elements
	case 5:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Less than, left elements
	case 6:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Greater than, left elements
	case 7:
		for( int y = 1; y < (int)inputs.size(); ++y )
			for( int x = 0; x < y; ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Equals to, right elements
	case 8:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] == inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Less than, right elements
	case 9:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] < inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Greater than, right elements
	case 10:
		for( int y = 0; y < (int)inputs.size() - 1; ++y )
			for( int x = y + 1; x < (int)inputs.size(); ++x )
				if( inputs[x] > inputs[y] )
					++outputs[y + start_index_output];
		break;
		// Continuous box of values
	case 11:
	{
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

			std::fill_n( outputs.begin() + start_index_output + y, count, count );
			y += count;
		}
		break;
	}
		// Sum
	case 12:
	{
		auto sum = std::accumulate( inputs.begin(), inputs.end(), 0.0 );
		std::fill_n( outputs.begin() + start_index_output, (int)inputs.size(), sum );
		break;
	}
	}
	// cout << "\nTransfo ouputs: ";
	// std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
}

// Comparison operations with 1 parameter
void interpreter_comparison( int number,
                             const vector<double>& inputs,
                             vector<double>& outputs,
                             double parameter )
{
	int start_index_output = number * (int)inputs.size();

	// cout << "\nCompar number: " << number << "\nCompar inputs: ";
	// std::copy( inputs.begin(), inputs.end(), ostream_iterator<double>( cout, " ") );

	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() + start_index_output );
		break;
		// Equals to parameter
	case 1:
		transform( inputs.begin(),
		           inputs.end(),
		           outputs.begin() + start_index_output,
		           [&parameter](const auto& y) -> double { return std::abs( parameter - y ); } );
		break;
		// Greater than parameter
	case 2:
		transform( inputs.begin(),
		           inputs.end(),
		           outputs.begin() + start_index_output,
		           [&parameter](const auto& y) -> double { return std::max( 0.0, parameter - y ); } );
		break;
		// Less than parameter
	case 3:
		transform( inputs.begin(),
		           inputs.end(),
		           outputs.begin() + start_index_output,
		           [&parameter](const auto& y) -> double { return std::max( 0.0, y - parameter ); } );
		break;
	}

	// cout << "\nCompar ouputs: ";
	// std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
}

// Comparison operations with 2 parameters
void interpreter_comparison( int number,
                             const vector<double>& inputs,
                             vector<double>& outputs,
                             double parameter_1,
                             double parameter_2 )
{
	int start_index_output = number * (int)inputs.size();

	switch( number )
	{
		// Identity
	case 0:
		copy( inputs.begin(), inputs.end(), outputs.begin() + start_index_output );
		break;
		// Inside [p1,p2]
	case 1:
		transform( inputs.begin(),
		           inputs.end(),
		           outputs.begin() + start_index_output,
		           [&](const auto& y) -> double { return inside( y, parameter_1, parameter_2); } );
		break;
		// Outside [p1,p2]
	case 2:
		transform( inputs.begin(),
		           inputs.end(),
		           outputs.begin() + start_index_output,
		           [&](const auto& y) -> double { return outside( y, parameter_1, parameter_2); } );
		break;
	}
}

void transformation_layer( const vector<double>& inputs,
                           vector<double>& outputs,
                           int nb_vars,
                           int nb_params,
                           const vector<int>& weights )
{
	for( int op_t = 0; op_t < number_units_transfo; ++op_t )
	{
		int number_units_compar;
		if( nb_params == 1 )
			number_units_compar = number_units_compar_1_param;
		else
			number_units_compar = number_units_compar_2_params;

		auto offset = op_t * number_units_compar;
		
		for( int op_c = 0; op_c < number_units_compar; ++op_c )
			if( weights[ offset + op_c ] == 1 )
			{
				interpreter_transformation( op_t, inputs, outputs );
				break;
			}
	}
}

int comparison_layer( const vector<double>& inputs,
                      vector<double>& outputs,
                      int nb_vars,
                      int nb_params,
                      const vector<int>& weights,
                      double parameter_1,
                      double parameter_2 )
{
	int nb_active_units = 0;
	
	int number_units_compar;
	if( nb_params == 1 )
		number_units_compar = number_units_compar_1_param;
	else
		number_units_compar = number_units_compar_2_params;

	vector<double> temp_inputs( nb_vars );
	bool need_to_compute_op_c = true; // small optimization to force triggering std::fill for the first time
	
	for( int op_c = 0; op_c < number_units_compar; ++op_c )
	{
		if( need_to_compute_op_c )
			std::fill( temp_inputs.begin(), temp_inputs.end(), 0.0 );
		need_to_compute_op_c = false;

		for( int op_t = 0; op_t < number_units_transfo; ++op_t )
		{
			auto offset = op_t * number_units_compar;
			if( weights[ offset + op_c ] == 1 )
			{
				for( int i = 0; i < nb_vars; ++i )
					temp_inputs[i] += inputs[ op_t * nb_vars + i ];
				if( !need_to_compute_op_c )
					need_to_compute_op_c = true;
			}			
		}

		if( need_to_compute_op_c )
		{
			++nb_active_units;
			if( nb_params == 1 )
				interpreter_comparison( op_c, temp_inputs, outputs, parameter_1 );
			else
				interpreter_comparison( op_c, temp_inputs, outputs, parameter_1, parameter_2 );				
		}
	}

	return nb_active_units;
}

double intermediate_g( const vector<int>& weights,
                       const vector<double>& inputs,
                       int nb_vars,
                       int nb_params,
                       double parameter_1,
                       double parameter_2 )
{
	// double max_cost = nb_vars + 0.9;

	int number_units_compar;
	if( nb_params == 1 )
		number_units_compar = number_units_compar_1_param;
	else
		number_units_compar = number_units_compar_2_params;

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

	vector<double> outputs_transfo( nb_vars * number_units_transfo );
	vector<double> outputs_compar( nb_vars * number_units_compar );
	// vector<double> outputs( nb_vars, 0.0 );
	// vector<double> outputs( nb_vars * number_units_compar );
	
	transformation_layer( inputs, outputs_transfo, nb_vars, nb_params, weights );

	auto nb_active_units = comparison_layer( outputs_transfo,
	                                         outputs_compar,
	                                         nb_vars,
	                                         nb_params,
	                                         weights,
	                                         parameter_1,
	                                         parameter_2 );

	// for( int i = 0; i < (int)outputs_compar.size(); ++i )
	// 	outputs[ i % nb_vars ] += outputs_compar[ i ];
		
	// std::transform( outputs_compar.begin(),
	//                 outputs_compar.end(),
	//                 outputs.begin(),
	//                 [&nb_vars](const auto& x){ return sigmoid( x, nb_vars ); } );

	// cout << "\nSigmoid outputs: ";
	// std::copy( outputs.begin(), outputs.end(), ostream_iterator<double>( cout, " ") );
	
	// return nb_vars * std::accumulate( outputs.begin(), outputs.end(), 0.0 ) / nb_active_units;
	/////
	// double normalized_sum = std::accumulate( outputs.begin(), outputs.end(), 0.0 ) / ( nb_active_units * nb_vars );

	// return max_cost * normalized_sum;
	/////
	// return std::accumulate( outputs.begin(), outputs.end(), 0.0 ) /( (double)std::count_if( outputs.begin(), outputs.end(), [](const auto& o){ return o > 0.0; } ) / 2 );
	return std::accumulate( outputs_compar.begin(), outputs_compar.end(), 0.0 ) / nb_active_units;
}

// // ref_wrapper<Variable> version
// double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int max )
// {
// 	int nb_vars = (int)vars.size();
// 	vector<double> inputs( nb_vars );
// 	vector<int> weights_int( weights.size() + number_functions );
// 	std::copy( vars.begin(), vars.end(), inputs.begin() );
// 	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get().get_value(); } );
	
// 	return intermediate_g( weights_int, inputs, nb_vars, max );
// }

// // Variable version
// double g( const vector< Variable >& weights, const vector<int>& vars, int max )
// {
// 	int nb_vars = (int)vars.size();
// 	vector<double> inputs( nb_vars );
// 	vector<int> weights_int( weights.size() + number_functions );
// 	std::copy( vars.begin(), vars.end(), inputs.begin() );
// 	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get_value(); } );

// 	return intermediate_g( weights_int, inputs, nb_vars, max );
// }

// // Flat vector version
// double g( const vector< reference_wrapper<Variable> >& weights, const vector<int>& vars, int start, int end, int max )
// {
// 	int nb_vars = end - start;
// 	vector<double> inputs( nb_vars );
// 	vector<int> weights_int( weights.size() + number_functions );
// 	std::copy( vars.begin() + start, vars.begin() + start + end, inputs.begin() );
// 	std::transform( weights.begin(), weights.end(), weights_int.begin(), []( auto& w ){ return w.get().get_value(); } );

// 	return intermediate_g( weights_int, inputs, nb_vars, max );
// }

// Int vector version
double g( const vector< int >& weights,
          const vector<double>& vars,
          int start,
          int end,
          int nb_params,
          double parameter_1,
          double parameter_2 )

{
	return intermediate_g( weights, vars, end - start, nb_params, parameter_1, parameter_2 );
}
