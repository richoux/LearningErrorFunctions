
#include <iostream>
#include <vector>

#include <ghost/solver.hpp>

#include "check.hpp"
#include "builder.hpp"
#include "user_print.hpp"

using namespace std::literals::chrono_literals;

int main( int argc, char **argv )
{
	int instance_size;
	int timeout;
	if( argc != 3 )
	{
		std::cout << "Usage: " << argv[0] << " instance_size_or_number timeout_in_seconds\n";
		return EXIT_FAILURE;
	}
	else
	{
		instance_size = std::stoi( argv[1] );
		timeout = std::stoi( argv[2] ) * 1000000;
	}
	
  Builder builder( instance_size );

  ghost::Solver solver( builder );
  ghost::Options options;
  options.print = std::make_shared<UserPrint>();
  
  double error = 0.;
  std::vector<int> solution;

  solver.solve( error, solution, timeout, options );

  check_solution( solution );
  
  return EXIT_SUCCESS;
}

