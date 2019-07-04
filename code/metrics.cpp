#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <limits>

#include "metrics.hpp"
#include "increment.hpp"

/*
 * Local functions
 */
// double convert_to_fractional( int number )
// {
// 	double frac = number;

// 	while( frac >= 1 )
// 		frac /= 10;

// 	return frac;
// }


// TODO and WARNING: this function assumes that all variables share the same domain [0, k-1]
int search_nearest_solution( const shared_ptr<Constraint> constraint,
                             const vector< reference_wrapper<Variable> > &variables,
                             const vector< int > &vars_to_search,
                             bool search_for_best = false )
{
	bool solution_found = false;
	bool reach_last_value = false;
	int difference = 0;
	int min_diff = std::numeric_limits<int>::max();

	vector<int> backup;
	for( int i = 0 ; i < vars_to_search.size() ; ++i )
	{
		backup.push_back( variables[ vars_to_search[ i ] ].get().get_value() );
		variables[ vars_to_search[ i ] ].get().set_value( 0 );
	}

	if( constraint->cost() == 0 )
	{
		solution_found = true;
		min_diff = 0;
		for( auto &original_value : backup )
			min_diff += original_value;
	}
	
	while( ( !solution_found || search_for_best ) && !reach_last_value )
	{
		increment_some_vars( variables, vars_to_search );

		if( constraint->cost() == 0 )
		{
			solution_found = true;

			for( int i = 0 ; i < vars_to_search.size() ; ++i )
				difference += std::abs( variables[ vars_to_search[ i ] ].get().get_value() - backup[ i ] );

			if( min_diff > difference )
				min_diff = difference;
		}

		reach_last_value = std::all_of( vars_to_search.begin(),
		                                vars_to_search.end(),
		                                [&]( auto index ){ return variables[index].get().get_value() == variables[index].get().get_domain_max_value(); } );
	};

	// roll-back
	for( int i = 0 ; i < vars_to_search.size() ; ++i )
		variables[ vars_to_search[ i ] ].get().set_value( backup[ i ] );

	if( solution_found )
		return min_diff;
	else
		return -1;
}


///////////////

// Limited to 20 variables so far
// TODO: something cleaner without this 20 vars limitation
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

			if( search_nearest_solution( constraint, variables, vars_to_search ) != -1 )
				return vars_to_search.size();
		}

		return -1;
	}
}

// Limited to 20 variables so far
// TODO: something cleaner without this 20 vars limitation
double hamming( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables )
{
	if( constraint->cost() == 0 )
		return 0;
	else
	{
		long counter_limit = (long)std::pow( 2, variables.size() ) - 1;
		vector<int> vars_to_search;
		int diff = 0;
		int min_diff = std::numeric_limits<int>::max();
		
		for( long counter = 1 ; counter <= counter_limit ; ++counter )
		{
			vars_to_search.clear();
			bitset<20> to_convert( counter );

			for( int i = 0 ; i < 20 ; ++i )
				if( to_convert[ i ] == 1 )
					vars_to_search.push_back( i );

			diff = search_nearest_solution( constraint, variables, vars_to_search, true );

			if( diff != -1 && min_diff > diff )
				min_diff = diff;
		}
				
		if( min_diff < std::numeric_limits<int>::max() )
			return min_diff;
		else
			return -1;
	}
}

// Limited to 20 variables so far
// TODO: something cleaner without this 20 vars limitation
double man_ham( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables )
{
	if( constraint->cost() == 0 )
		return 0;
	else
	{
		long counter_limit = (long)std::pow( 2, variables.size() ) - 1;
		vector<int> vars_to_search;
		int diff = 0;
		int min_diff = std::numeric_limits<int>::max();
		int number_vars_to_check = std::numeric_limits<int>::max();
		
		for( long counter = 1 ; counter <= counter_limit ; ++counter )
		{
			vars_to_search.clear();
			bitset<20> to_convert( counter );

			for( int i = 0 ; i < 20 ; ++i )
				if( to_convert[ i ] == 1 )
					vars_to_search.push_back( i );

			diff = search_nearest_solution( constraint, variables, vars_to_search, true );

			if( diff != -1 && number_vars_to_check >= vars_to_search.size() )
			{
				if( number_vars_to_check > vars_to_search.size() )
				{
					number_vars_to_check = vars_to_search.size();
					min_diff = diff;
				}
				else
					if( min_diff > diff )
						min_diff = diff;						
			}
		}

		if( number_vars_to_check < std::numeric_limits<int>::max() )
			// return #vars.min_diff
			return number_vars_to_check + ( (double)min_diff / ( std::pow( 10, std::floor( std::log10( min_diff ) ) + 1 ) ) );
			// return number_vars_to_check + convert_to_fractional( min_diff );
		else
			return -1;
	}
}

