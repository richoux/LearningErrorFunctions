#include <random>
#include <cmath>
#include <algorithm>
#include <set>
#include <utility>
#include <iterator>

#include <iostream>

#include "obj_hamming.hpp"
#include "function_to_learn_cppn.hpp"
#include "../utils/convert.hpp"

Obj_hamming::Obj_hamming( unique_ptr<Concept> concept,
                          int nb_vars,
                          int nb_params,
                          int parameter_1,
                          int parameter_2,
                          const vector<int>& random_solutions,
                          const vector<int>& samples,
                          const map<string, double>& cost_map )
	: Objective( "Min difference with the Hamming distance" ),
	  _concept( std::move( concept ) ),
	  _nb_vars( nb_vars ),
	  _nb_params( nb_params ),
	  _param_1( parameter_1 ),
	  _param_2( parameter_2 ),
	  _random_sol( random_solutions ),
	  _random_config( samples ),
	  _cost_map( cost_map )
{ }

double Obj_hamming::required_cost( const vector< Variable >& weights ) const
{
	set< pair<double, double> > costs;
	double cost = 0.0;

	for( int i = 0; i < (int)_random_sol.size(); i += _nb_vars )
	{
		auto s = g( weights, _random_sol, _nb_vars, i, _nb_params, _param_1, _param_2 );
		
#if defined DEBUG
		std::copy( _random_sol.begin() + i, _random_sol.begin() + i + _nb_vars, ostream_iterator<int>( cout, " "));
		cout << ": (0, " << s << ")\n";
#endif
		if( s != 0 )
			++cost;
	}
	
	for( int i = 0; i < (int)_random_config.size(); i += _nb_vars )
	{
#if defined DEBUG
		std::copy( _random_config.begin() + i, _random_config.begin() + i + _nb_vars, ostream_iterator<int>( cout, " "));
		auto f = _cost_map.at( convert( _random_config, i, i + _nb_vars ) );
		auto s = g( weights, _random_config, _nb_vars, i, _nb_params, _param_1, _param_2 );
		cout << ": (" << f << ", " << s << ")\n";
		costs.emplace( f, s );
#else
		costs.emplace( _cost_map.at( convert( _random_config, i, i + _nb_vars ) ),
		               g( weights, _random_config, _nb_vars, i, _nb_params, _param_1, _param_2 ) );
#endif
	}
	
#if defined DEBUG
	cout << "\n//////////////\n\n";
	
	for( auto c : costs )
		cout << "(" << c.first << ", " << c.second << ")\n";
#endif
	
	for( auto it = costs.begin(); std::next( it ) != costs.end(); ++it )
	{
		if( (*it).second > (*std::next( it )).second )
			++cost;
	}
	
	return cost;
}
