#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

std::vector<std::string> get_next_line_and_split_into_tokens( std::istream &str )
{
	std::vector<std::string> result;
	std::string line;
	std::getline( str, line );

	std::stringstream lineStream( line );
	std::string cell;

	while( std::getline( lineStream, cell, ',' ) )
	{
		result.push_back( cell );
	}

	// This checks for a trailing comma with no data after it.
	if( !lineStream && cell.empty() )
	{
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	
	return result;
}

int main( int argc, char *argv[] )
{
	std::ifstream file( "all-diff_6.csv" );
	auto dummy = get_next_line_and_split_into_tokens( file );
	int number_dimension = dummy.size() - 3;
	
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	int new_dimension = static_cast<int>( std::floor( std::log2( number_dimension ) ) );
	std::normal_distribution<> gaussian{ 0, 1. / std::sqrt( new_dimension ) }; // N(0, 1/sqrt(k))

	std::vector< std::vector<double> > new_space( new_dimension );
	for( int i = 0; i < new_dimension; ++i )
		new_space[i].reserve( number_dimension );

	for( int dim = 0; dim < new_dimension; ++dim )
		for( int i = 0; i < number_dimension; ++i )
			new_space[dim][i] = gaussian( gen );

	// for( int dim = 0; dim < new_dimension; ++dim )
	// {
	// 	for( int i = 0; i < number_dimension; ++i )
	// 		std::cout << new_space[dim][i] << " ";
	// 	std::cout << "\n";
	// }

	std::vector<double> x( number_dimension );
	std::vector<double> y( 3 );
	std::vector<double> new_x( new_dimension );

	std::cout << "Hamming,Manhattan,Mix";
	for( int dim = 0; dim < new_dimension; ++dim )
		std::cout << ",v" << dim;
	std::cout << "\n";
	
	while( file.good() )
	{
		auto tokens = get_next_line_and_split_into_tokens( file );

		for( int i = 0; i < 3; ++i )
			y[i] = std::stod( tokens[i] );

		for( int i = 0; i < number_dimension; ++i )
			x[i] = std::stod( tokens[i+3] );
			
		// for( auto it = tokens.begin() + 3; it < tokens.end(); ++it )
		// 	x.push_back( std::stod( *it ) );

		std::fill( new_x.begin(), new_x.end(), 0. );
		
		for( int dim = 0; dim < new_dimension; ++dim )
			for( int i = 0; i < number_dimension; ++i )
				new_x[dim] += ( x[i] * new_space[dim][i] );

		// print
		std::cout << y[0] << ","
		          << y[1] << ","
		          << y[2];
		for( int dim = 0; dim < new_dimension; ++dim )
			std::cout << "," << new_x[dim];
		std::cout << "\n";
	}

	return EXIT_SUCCESS;
}
