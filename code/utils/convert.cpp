#include "convert.hpp"

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
