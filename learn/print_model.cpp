#include <string>

#include "../utils/print.hpp"

int main( int argc, char** argv )
{
	print_model( std::string( argv[1] ) );
	
	return EXIT_SUCCESS;
}
