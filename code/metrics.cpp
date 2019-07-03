#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>

#include "metrics.hpp"
#include "increment.hpp"

/*
 * Local functions
 */

// WARNING: this function assumes that all variables share the same domain [0, k-1]
double search_nearest_solution( const shared_ptr<Constraint> constraint,
                                const vector< reference_wrapper<Variable> > &variables,
                                const vector< int > &vars_to_search )
{
	bool solution_found = false;
	bool reach_last_value = false;
	double difference = 0.;

	
	vector<int> backup;
	for( int i = 0 ; i < vars_to_search.size() ; ++i )
	{
		backup.push_back( variables[ vars_to_search[ i ] ].get().get_value() );
		variables[ vars_to_search[ i ] ].get().set_value( 0 );
	}

	if( constraint->cost() == 0 )
		solution_found = true;
	
	while( !solution_found && !reach_last_value )
	{
		increment_some_vars( variables, vars_to_search );
		
		if( constraint->cost() == 0 )
			solution_found = true;

		reach_last_value = std::all_of( vars_to_search.begin(), vars_to_search.end(), [&]( auto index ){ return variables[index].get().get_value() == variables[index].get().get_domain_max_value(); } );
	};
	
	// roll-back and compute the sum of absolute differences of values
	for( int i = 0 ; i < vars_to_search.size() ; ++i )
	{
		int index = vars_to_search[ i ];

		// WARNING: will not work for Hamming distance. We need to check ALL possible solutions
		// and to keep the closest one. Early stopping with the first solution will not work here.
		if( solution_found )
			difference += std::abs( variables[ index ].get().get_value() - backup[ i ] );
		variables[ index ].get().set_value( backup[ i ] );
	}

	if( solution_found )
		return difference;
	else
		return -1;
}


///////////////

// Limited to 20 variables so far
double manhattan( const shared_ptr<Constraint> constraint,
                  const vector< reference_wrapper<Variable> >& variables )
{
	if( constraint->cost() == 0 )
		return 0;
	else
	{
		long counter_limit = (long)std::pow( 2, variables.size() ) - 1;
		vector<int> vars_to_search;

		for( long counter = 1 ; counter <= counter_limit ; ++counter )
		{
			vars_to_search.clear();
			bitset<20> to_convert( counter );

			for( int i = 0 ; i < 20 ; ++i )
				if( to_convert[ i ] == 1 )
					vars_to_search.push_back( i );

			// std::cout << counter << "/" << counter_limit << " " << to_convert << "\n";
			// for( auto &v : vars_to_search )
			// 	std::cout << v << " ";
			// std::cout << "\n";

			if( search_nearest_solution( constraint, variables, vars_to_search ) != -1 )
				return vars_to_search.size();
		}
		
		return -1;
	}
}

double hamming( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables )
{
	// TODO
	return 0.;
}

double man_ham( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables )
{
	// TODO, return man.ham
	return 0.;
}

