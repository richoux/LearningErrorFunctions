#include <algorithm>

#include "print.hpp"
#include "../learn/function_to_learn_cppn.hpp" // for number_functions

string transfo_operation( int number )
{
	switch( number )
	{
	case 0:
		return "    Identity";
		break;
	case 1:
		return "Number of elements on the right equals to y";
		break;
	case 2:
		return "Number of elements on the right smaller than y";
		break;
	case 3:
		return "Number of elements on the right greater than y";
		break;
	case 4:
		return "Number of elements on the left equals to y";
		break;
	case 5:
		return "Number of elements on the left smaller than y";
		break;
	case 6:
		return "Number of elements on the left greater than y";
		break;
	case 7:
		return "Number of elements equals to y + param";
		break;
	case 8:
		return "Number of elements smaller than y + param";
		break;
	case 9:
		return "Number of elements greater than y + param";
		break;
	case 10:
		return "Max(0, y - param)";
		break;
	case 11:
		return "Max(0, param - y)";
		break;
	case 12:
		return "Max(0, x_i - x_i+1 )";
		break;
	case 13:
		return "Max(0, x_i+1 - x_i )";
		break;
	case 14:
		return "Number of elements equals to y";
		break;
	case 15:
		return "Number of elements greater than y";
		break;
	case 16:
		return "Number of elements smaller than y";
		break;
	case 17:
		return "Number of elements greater than or equals to y AND less than or equals to y + param";
		break;
	default:
		return "";
	}
}

string compar_operation( int number )
{
	switch( number )
	{
	case 0:
		return "    Identity";
		break;
	case 1:
		return "Input equals to parameter";
		break;
	case 2:
		return "Input greater than or equals to parameter";
		break;
	case 3:
		return "Input less than or equals to parameter";
		break;
	case 4:
		return "Euclidian division of the difference between input and parameter with domain size";
		break;
	case 5:
		return "Input equals to the number of variables";
		break;
	case 6:
		return "Input greater than or equals to the number of variables";
		break;
	case 7:
		return "Input less than or equals to the number of variables";
		break;
	default:
		return "";
	}	
}

void print_model( const Indi& indi )
{
	vector<int> vec( indi.size() );
	std::copy( indi.begin(), indi.end(), vec.begin() );
	print_model( vec );
}

void print_model( const string& indi )
{
	vector<int> vec;
	for( const char& c : indi )
		vec.push_back( stoi( std::string(1, c) ) );
	print_model( vec );
}

void print_model( const vector<int>& indi )
{
	string arith = indi[ number_units_transfo ] ? "\t x" : "\t +";
	string agreg = indi[ number_units_transfo + 1 ] ? "       Sum" : "   Count #x > 0";
	auto number_active_transfo_units = std::count( indi.begin(), indi.begin() + number_units_transfo, true );
	
	for( int i = 0; i < number_units_transfo; ++i )
		if( indi[i] )
		{
			cout << transfo_operation(i) << "\n";
			if( --number_active_transfo_units > 0 )
				cout << arith << "\n";
		}

	cout << "\t|\n"
	     << "\tv\n"
	     << agreg << "\n"
	     << "\t|\n"
	     << "\tv\n";

	for( int i = 0; i < number_units_compar; ++i )
		if( indi[i + number_units_transfo + 2 ] )
		{
			cout << compar_operation(i) << "\n";
			break;
		}
}
