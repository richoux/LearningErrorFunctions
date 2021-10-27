#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "user_print.hpp"

stringstream UserPrint::print_candidate( const std::vector<Variable>& variables ) const
{
	stringstream stream;

	int nb_vars = static_cast<int>( variables.size() );
	int order = static_cast<int>( std::sqrt( nb_vars ) );
	int space = ceil( log10( nb_vars ) ) + 1;
	
	stream << "Solution:";

	for( int i = 0 ; i < nb_vars ; ++i )
	{
		if( i%order == 0 )
			stream << "\n";

		stream << std::setw( space ) << variables[i].get_value();
	}
	
	stream << "\n";

	return stream;
}
