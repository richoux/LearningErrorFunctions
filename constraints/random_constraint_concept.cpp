#include <algorithm>

// #include <iostream>
// #include <iterator>

#include "random_constraint_concept.hpp"
#include "../utils/convert.hpp"

RandomConcept::RandomConcept( int nb_vars, int max_value )
	: Concept( nb_vars, max_value )
{
	// 1% of the configuration space
	unsigned long long int number_solutions = static_cast<unsigned long long int>( std::pow( max_value, nb_vars ) / 100 );

	vector<int> sample( nb_vars );
	for( unsigned long long int i = 0; i < number_solutions; ++i )
	{
		_rng.generate( sample, 1, max_value );

		// std::copy( sample.begin(), sample.end(), ostream_iterator<int>( cout, " " ) );
		// cout << "\n";
		
		_solutions.push_back( convert( sample ) );
	}

	// _solutions.push_back( "0_1_2_3_4_" );	
}

RandomConcept::RandomConcept()
	: Concept( 0, 0 )
{ }

bool RandomConcept::concept_( const vector<int>& var, int start, int end ) const
{
	string config = convert( var, start, end );
	return std::find( _solutions.begin(), _solutions.end(), config ) != _solutions.end();
}

bool RandomConcept::concept_( const vector< reference_wrapper<Variable> >& var ) const
{
	vector<int> var_int( var.size() );
	std::transform( var.begin(), var.end(), var_int.begin(), []( auto& v ){ return v.get().get_value(); } );
	
	string config = convert( var_int );
	return std::find( _solutions.begin(), _solutions.end(), config ) != _solutions.end();
}
