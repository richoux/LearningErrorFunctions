#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "user_print.hpp"

stringstream UserPrint::print_candidate( const std::vector<Variable>& variables ) const
{
	stringstream stream;

	if( variables.size() != 20 )
	{
		stream << "Solution:\n";
		int max_element = std::numeric_limits<int>::min();
		for( const auto& var : variables )
			if( max_element < var.get_value() )
				max_element = var.get_value();

		int indent_values = std::ceil( std::log10( max_element ) ) + 1;
		int indent_indexes = std::ceil( std::log10( static_cast<int>( variables.size() ) ) );
		for( int i = 0 ; i < static_cast<int>( variables.size() ) ; ++i )
		{
			if( i % 10 == 0 )
			{
				if( i != 0 )
					stream << "\n";
				stream << "v[" << std::setw( indent_indexes ) << i << "]:" << std::setw( indent_values ) << variables[i].get_value();
			}
			else
				stream << ", v[" << std::setw( indent_indexes ) << i << "]:" << std::setw( indent_values ) << variables[i].get_value();
		}
		stream << "\n";
	}
	else
	{
		stream << "Solution:\n\n";

		if( variables[0].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << " - ";

		if( variables[1].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[2].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[3].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[4].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << "\n";
		stream << "| \\ |     / | X |";
		stream << "\n";

		if( variables[9].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << " - ";

		if( variables[8].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[7].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[6].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[5].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << "\n";
		stream << "  \\ |   | / |   |";
		stream << "\n";

		if( variables[11].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << " - ";

		if( variables[10].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << "   ";
		
		if( variables[15].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[16].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << "   ";
		
		if( variables[19].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << "\n";
		stream << "|     \\ |   |   ";
		stream << "\n";

		if( variables[12].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << " - ";

		if( variables[13].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[14].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << "   ";
		
		if( variables[17].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";
	
		stream << " - ";
		
		if( variables[18].get_value() == 2 )
			stream << "\033[1;31mO\033[0m";
		else
			stream << "O";

		stream << "\n";
	}
	
	return stream;
}
