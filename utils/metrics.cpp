#include <limits>

#include "metrics.hpp"

double hamming_metric( const vector<int>& configuration,
                       const vector<int>& solution,
                       int start_config,
                       int start_sol,
                       int nb_vars )
{
	double cost = 0.;
	
	for( int i = 0; i < nb_vars; ++i )
		if( configuration[ start_config + i ] != solution[ start_sol + i ] )
			++cost;

	return cost;
}

double manhattan_metric( const vector<int>& configuration,
                         const vector<int>& solution,
                         int start_config,
                         int start_sol,
                         int nb_vars )
{
	double diff = 0.;
	
	for( int i = 0; i < nb_vars; ++i )
		if( configuration[ start_config + i ] != solution[ start_sol + i ] )
			diff += std::abs( solution[ start_sol + i ] - configuration[ start_config + i ] );

	return diff;
}

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

	return cost + diff;
}

map<string, double> compute_metric( const vector<int>& random_solutions,
                                    const vector<int>& random_configurations,
                                    int nb_vars,
                                    int max_value )
{
	map<string, double> costs;

	for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		costs[ convert( random_solutions, s, s + nb_vars ) ] = 0.;
	
	double cost;
	double min_cost;
	
	for( int c = 0; c < (int)random_configurations.size(); c += nb_vars )
	{
		min_cost = std::numeric_limits<double>::max();

		for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		{
			cost = hamming_manhattan_metric( random_configurations, random_solutions, c, s, nb_vars, max_value );
			if( cost < min_cost )
				min_cost = cost;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ] = min_cost;
	}

	return costs;
}

map<string, double> compute_metric_hamming_only( const vector<int>& random_solutions,
                                                 const vector<int>& random_configurations,
                                                 int nb_vars )
{
	map<string, double> costs;

	for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		costs[ convert( random_solutions, s, s + nb_vars ) ] = 0.;
	
	double cost;
	double min_cost;
	
	for( int c = 0; c < (int)random_configurations.size(); c += nb_vars )
	{
		min_cost = std::numeric_limits<double>::max();

		for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		{
			cost = hamming_metric( random_configurations, random_solutions, c, s, nb_vars );
			if( cost < min_cost )
				min_cost = cost;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ] = min_cost;
	}

	return costs;
}

map<string, double> compute_metric_manhattan_only( const vector<int>& random_solutions,
                                                   const vector<int>& random_configurations,
                                                   int nb_vars )
{
	map<string, double> costs;

	for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		costs[ convert( random_solutions, s, s + nb_vars ) ] = 0.;
	
	double cost;
	double min_cost;
	
	for( int c = 0; c < (int)random_configurations.size(); c += nb_vars )
	{
		min_cost = std::numeric_limits<double>::max();
		
		for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		{
			cost = manhattan_metric( random_configurations, random_solutions, c, s, nb_vars );
			if( cost < min_cost )
				min_cost = cost;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ] = min_cost;
	}

	return costs;
}

map<string, pair<double,double>>
compute_metric_hamming_and_manhattan( const vector<int>& random_solutions,
                                      const vector<int>& random_configurations,
                                      int nb_vars )
{
	map<string, pair<double,double>> costs;

	for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
	{
		costs[ convert( random_solutions, s, s + nb_vars ) ].first = 0.;
		costs[ convert( random_solutions, s, s + nb_vars ) ].second = 0.;
	}
	
	double cost_hamming;
	double cost_manhattan;
	double min_cost_hamming;
	double min_cost_manhattan;
	
	for( int c = 0; c < (int)random_configurations.size(); c += nb_vars )
	{
		min_cost_hamming = std::numeric_limits<double>::max();
		min_cost_manhattan = std::numeric_limits<double>::max();

		for( int s = 0; s < (int)random_solutions.size(); s += nb_vars )
		{
			cost_hamming = hamming_metric( random_configurations, random_solutions, c, s, nb_vars );
			if( cost_hamming < min_cost_hamming )
				min_cost_hamming = cost_hamming;

			cost_manhattan = manhattan_metric( random_configurations, random_solutions, c, s, nb_vars );
			if( cost_manhattan < min_cost_manhattan )
				min_cost_manhattan = cost_manhattan;
		}

		costs[ convert( random_configurations, c, c + nb_vars ) ].first = min_cost_hamming;
		costs[ convert( random_configurations, c, c + nb_vars ) ].second = min_cost_manhattan;
	}

	return costs;
}
