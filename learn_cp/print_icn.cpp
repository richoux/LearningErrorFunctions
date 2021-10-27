#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "print_icn.hpp"
#include "../learn_ga/function_to_learn_icn.hpp" // for number_functions
#include "../utils/print.hpp" // for some functions

stringstream PrintICN::print_candidate( const std::vector<Variable>& variables ) const
{
	stringstream stream;
	
	stream << "Function: ";
	for( int i = 0 ; i < static_cast<int>( variables.size() ) ; ++i )
		stream << variables[i].get_value();
	stream << "\n\n";

	string arith = variables[ number_units_transfo ].get_value() == 1 ? "\t x" : "\t +";
	string agreg = variables[ number_units_transfo + 1 ].get_value() == 1 ? "       Sum" : "   Count #x > 0";

	int number_active_transfo_units = 0;
	for( int i = 0 ; i < number_units_transfo ; ++i )
		number_active_transfo_units += variables[i].get_value();
		
	for( int i = 0 ; i < number_units_transfo ; ++i )
		if( variables[i].get_value() == 1 )
		{
			stream << transfo_operation(i) << "\n";
			if( --number_active_transfo_units > 0 )
				stream << arith << "\n";
		}

	stream << "\t|\n"
	       << "\tv\n"
	       << agreg << "\n"
	       << "\t|\n"
	       << "\tv\n";

	for( int i = 0 ; i < number_units_compar ; ++i )
		if( variables[i + number_units_transfo + 2 ].get_value() == 1 )
		{
			stream << compar_operation(i) << "\n";
			break;
		}
		
	stream << "\n";
	
	return stream;
}
