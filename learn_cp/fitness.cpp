#include <sstream>
#include <cmath>

#include "fitness.hpp"

#include "../utils/randutils.hpp"
#include "../utils/metrics.hpp"
#include "../utils/random_draw.hpp"
#include "../utils/convert.hpp"
#include "../utils/print.hpp"

#include "../constraints/concept.hpp"
#include "../constraints/all-diff_concept.hpp"
#include "../constraints/linear-eq_concept.hpp"
#include "../constraints/linear-leq_concept.hpp"
#include "../constraints/linear-geq_concept.hpp"
#include "../constraints/less-than_concept.hpp"
#include "../constraints/connection-min-gt_concept.hpp"
#include "../constraints/overlap-1d_concept.hpp"

Fitness::Fitness( const vector<Variable>& variables,
                  const string& input_file_path,
                  const vector<int>& random_solutions,
                  const vector<int>& random_configurations )
	: Minimize( variables, "Fitness" ),
	  _input_file_path( input_file_path ),
	  _nb_vars( static_cast<int>( variables.size() ) ),
	  _random_solutions( random_solutions ),
	  _random_configurations( random_configurations )
{
	double manhattan_cost;
	std::string input_costs_file_path = _input_file_path.substr( 0, _input_file_path.length() - 4 ) + std::string("_costs.txt");
	ifstream input_costs_file.open( input_costs_file_path );
	string line;

	while( getline( input_costs_file, line ) )
	{
		auto delimiter = line.find(" ");
		std::string solution_token = line.substr( 0, delimiter );
		line.erase(0, delimiter + 1 );
		delimiter = line.find(" ");
		std::string hamming_cost = line.substr( 0, delimiter );
		line.erase(0, delimiter + 1 );
		stringstream line_stream( line );
		line_stream >> manhattan_cost;
		cost_map.emplace( solution_token, std::pair<double,double>( std::stod( hamming_cost ), manhattan_cost ) );
	}
	
	input_costs_file.close();
}

double Fitness::required_cost( const vector<Variable*>& variables ) const
{
	double sum_costs_hamming = 0.0;
	double sum_costs_manhattan = 0.0;
	
	vector<int> weights( variables.size(), 0 );
	for( int i = 0; i < (int)variables.size(); ++i )
		if( variables[i].get_value() == 1 )
			weights[i] = 1;
			
	for( int i = 0; i < (int)random_solutions.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( random_solutions.begin() + i, random_solutions.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = cost_map.at( convert( random_solutions, i, i + nb_vars ) );
		auto s = g( weights, params, random_solutions, max_value, i, nb_vars );

		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << "\n";
#endif
	}
	
	for( int i = 0; i < (int)random_configurations.size(); i += nb_vars )
	{
#if defined DEBUG
		std::copy( random_configurations.begin() + i, random_configurations.begin() + i + nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = cost_map.at( convert( random_configurations, i, i + nb_vars ) );
		auto s = g( weights, params, random_configurations, max_value, i, nb_vars );

		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << "\n";
#endif
	}

	// Normalizing individual cost (after computing the sums, but it doesn't matter)
	// This is to have a fair comparison between Hamming and Manhattan costs,
	// otherwise Hamming would always be the smallest one.
	// Normalization for Hamming: division by the number of variables
	// Normalization for Manhattan: division by the number of variables times the maximal gap of values (here, max_value - min_value = max_value - 1)
	sum_costs_hamming /= nb_vars;
	sum_costs_manhattan /= ( nb_vars * ( max_value - 1 ) );
	
	double final_cost = std::min( sum_costs_hamming, sum_costs_manhattan );
	
	// penalize a network vector full of zeros
	if( std::count( weights.begin(), weights.begin() + number_units_transfo, 1 ) == 0 )
		final_cost += ( 10 * training_size );
	// penalty if no unique comparison function
	if( std::count( std::prev( weights.end(), number_units_compar ), weights.end(), 1 ) != 1 )
		final_cost += ( 10 * training_size );	
	// Huge penalty if the network does not use any operations with parameters although the user provides one (or some),
	// or if there is at least one operation with parameters although the user did not provide any.
	if( ( has_parameters && no_parameter_operations( weights ) ) || ( !has_parameters && !no_parameter_operations( weights ) ) )
		final_cost += ( 1000 * training_size );

	// favor models with fewer operations
	auto number_active_transfo_units = std::count( weights.begin(), weights.begin() + number_units_transfo, 1 );
	final_cost += ( static_cast<double>( number_active_transfo_units ) / number_units_transfo );

	return final_cost;
}
