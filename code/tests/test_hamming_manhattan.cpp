#include <vector>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double hamming_manhattan_metric( const vector<int>& configuration,
                                 const vector<int>& solution,
                                 int start_config,
                                 int start_sol,
                                 int nb_vars,
                                 int max_value )
{
	double cost = 0.;
	double diff = 0.;

	int max_diff = nb_vars * max_value;
	
	for( int i = 0; i < nb_vars; ++i )
		if( configuration[ start_config + i ] != solution[ start_sol + i ] )
		{
			cost += 1;
			diff += std::abs( solution[ start_sol + i ] - configuration[ start_config + i ] );
		}

	// normalization
	diff = 0.9 * ( diff / max_diff );

	//cost += ( diff / ( std::pow( 10, std::floor( std::log10( diff ) ) + 1 ) ) );
	
	return cost + diff;
}


int main( int argc, char **argv )
{
	vector<int> config{ 0, 8, 4, 3, 4, 5, 5, 7, 5 }; // 4.1625
	vector<int> solution{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	cout << hamming_manhattan_metric( config, solution, 0, 0, 9, 8 ) << "\n";
	return EXIT_SUCCESS;
}
