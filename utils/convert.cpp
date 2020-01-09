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

std::vector<int> revert( std::string s )
{
	std::vector<int> vec;

	size_t pos = 0;
	std::string token;
	while( ( pos = s.find( "_" ) ) != std::string::npos )
	{
		token = s.substr(0, pos);
		vec.push_back( std::stoi( token ) );
    s.erase(0, pos + 1);
	}
	
	return vec;
}


std::vector<int> make_weights( const std::vector<int>& raw_weights )
{
	int number_units_compar = ( (int)raw_weights.size() - number_units_aggreg ) - number_units_transfo;
	vector<int> network_weights( number_units_compar * number_units_transfo + number_units_aggreg, 0 );

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

std::vector<int> recover_raw_weights( const std::vector<int>& weights )
{
	int number_units_compar = ( (int)weights.size() - number_units_aggreg ) / number_units_transfo;
	vector<int> raw_weights( number_units_compar + number_units_transfo + number_units_aggreg, 0 );

	for( int c = 0; c < number_units_compar; ++c )
		for( int t = 0; t < number_units_transfo; ++t )
				if( weights[ t*number_units_compar + c ] == 1 )
				{
					raw_weights[ t ] = 1;
					raw_weights[ number_units_transfo + c ] = 1;
				}
	
	std::copy( std::prev( weights.end(), number_units_aggreg ),
	           weights.end(),
	           raw_weights.begin() + number_units_compar + number_units_transfo );
	
	return raw_weights;	
}
