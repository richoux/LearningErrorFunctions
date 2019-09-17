#include "convert.hpp"

std::string convert( const std::vector<int>& vec )
{
	std::string key = "";
	// sum is to limit possible collisions
	int sum = 0;
	
	for( auto v : vec )
	{
		key += std::to_string( v );
		sum += v;
	}
	key += std::to_string( sum );

	return key;
}
