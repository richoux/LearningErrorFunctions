#include "convert.hpp"
#include "../learn/function_to_learn_cppn.hpp"

std::string convert( const std::vector<int>& vec )
{
	std::string key = "";
	
	for( auto v : vec )
		key += std::to_string( v ) + "_";

	return key;
}

std::string convert( const std::vector<int>& vec, int start, int end )
{
	std::string key = "";
	
	for( int i = start; i < end; ++i )
		key += std::to_string( vec[i] )  + "_";

	return key;
}

std::vector<int> make_weights( const std::vector<int>& raw_weights )
{
	int number_units_compar = ( (int)raw_weights.size() - number_agregation_functions ) - number_units_transfo;
	vector<int> network_weights( number_units_compar * number_units_transfo + number_agregation_functions, 0 );

	for( int c = 0; c < number_units_compar; ++c )
		if( raw_weights[ number_units_transfo + c ] == 1 )
			for( int t = 0; t < number_units_transfo; ++t )
				if( raw_weights[ t ] == 1 )
					network_weights[ t * number_units_compar + c ] = 1;

	std::copy( raw_weights.begin() + number_units_compar + number_units_transfo,
	           raw_weights.end(),
	           network_weights.begin() + number_units_compar * number_units_transfo );
	
	return network_weights;	
}
