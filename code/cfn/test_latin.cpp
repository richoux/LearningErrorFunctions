#include <iostream>
#include <string>

#include "latin.hpp"

int main( int argc, char **argv )
{
	vector< ghost::Variable > vec;

	int size;
	if( argc == 1 )
		size = 10;
	else
		size = std::stoi( argv[1] );
	
	for( int i = 0; i < size; ++i )
		vec.emplace_back( std::string("v") + std::to_string(i),
		                  std::string("v") + std::to_string(i),
		                  0,
		                  size );

	vector< reference_wrapper<ghost::Variable> > vec_ref( vec.begin(), vec.end() );

	auto samples = LHS( vec_ref );

	for( int i = 0; i < size; ++i )
	{
		for( int j = 0; j < size; ++j )
			cout << samples[i][j] << " ";
		cout << "\n";
	}
	
	return EXIT_SUCCESS;
}
