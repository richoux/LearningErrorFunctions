#include <sstream>
#include <cmath>

#include "fitness.hpp"

#include "../learn_ga/function_to_learn_icn.hpp" // for number_functions and g-functions

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
                  const map<string, pair<double,double>>& cost_map,
                  const vector<int>& random_solutions,
                  const vector<int>& random_configurations,
                  int nb_vars,
                  int max_value,
                  const vector<double>& params )
	: Minimize( variables, "Fitness" ),
	  _cost_map( cost_map ),
	  _random_solutions( random_solutions ),
	  _random_configurations( random_configurations ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value ),
	  _params( params )
{ }

double Fitness::required_cost( const vector<Variable*>& variables ) const
{
	double sum_costs_hamming = 0.0;
	double sum_costs_manhattan = 0.0;
	
	vector<int> weights( variables.size(), 0 );
	for( int i = 0; i < (int)variables.size(); ++i )
		if( variables[i]->get_value() == 1 )
			weights[i] = 1;
			
	for( int i = 0; i < (int)_random_solutions.size(); i += _nb_vars )
	{
#if defined DEBUG
		std::copy( _random_solutions.begin() + i, _random_solutions.begin() + i + _nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = _cost_map.at( convert( _random_solutions, i, i + _nb_vars ) );
		auto s = g( weights, _params, _random_solutions, _max_value, i, _nb_vars );

		// if( s == std::numeric_limits<double>::max() )
		// 	s = 10000;
		
		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << ", Estimated: " << s << "\n";
#endif
	}
	
	for( int i = 0; i < (int)_random_configurations.size(); i += _nb_vars )
	{
#if defined DEBUG
		std::copy( _random_configurations.begin() + i, _random_configurations.begin() + i + _nb_vars, ostream_iterator<int>( cout, " "));
		cout << "\n";
#endif
		
		auto f = _cost_map.at( convert( _random_configurations, i, i + _nb_vars ) );
		auto s = g( weights, _params, _random_configurations, _max_value, i, _nb_vars );

		// if( s == std::numeric_limits<double>::max() )
		// 	s = 10000;

		sum_costs_hamming += std::abs( f.first - s );
		sum_costs_manhattan += std::abs( f.second - s );

#if defined DEBUG
		cout << "Hamming: " << f.first << ", Manhattan: " << f.second << ", Estimated: " << s << "\n";
#endif
	}

	// Normalizing individual cost (after computing the sums, but it doesn't matter)
	// This is to have a fair comparison between Hamming and Manhattan costs,
	// otherwise Hamming would always be the smallest one.
	// Normalization for Hamming: division by the number of variables
	// Normalization for Manhattan: division by the number of variables times the maximal gap of values (here, max_value - min_value = max_value - 1)
	sum_costs_hamming /= _nb_vars;
	sum_costs_manhattan /= ( _nb_vars * ( _max_value - 1 ) );
	
	double final_cost = std::min( sum_costs_hamming, sum_costs_manhattan );

#if defined DEBUG
	cout << "Estimated Hamming: " << sum_costs_hamming << ", Manhattan: " << sum_costs_manhattan << "\n";
#endif

	// favor models with fewer operations
	auto number_active_transfo_units = std::count( weights.begin(), weights.begin() + number_units_transfo, 1 );
	final_cost += ( static_cast<double>( number_active_transfo_units ) / number_units_transfo );

	return final_cost;
}
