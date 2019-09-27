#include <random>
#include <cmath>

#if defined CHRONO
#include <chrono>
#endif

#include "obj_max_outputs.hpp"
#include "function_to_learn_cppn.hpp"
//#include "function_to_learn_trigo.hpp"
#include "concept.hpp"

#if defined CHRONO
static bool first = true;
#endif

Obj_MO::Obj_MO( int nb_vars, int max_value )
	: Objective( "Max Outputs" ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value )
{ }

double Obj_MO::required_cost( const vector< Variable >& variables ) const
{
#if defined CHRONO
	auto start = std::chrono::steady_clock::now();
#endif

	double total = 0.;
	vector<int> sample( _nb_vars );
	_rng.generate( sample, 0, _max_value );

	for( int i = 0; i < 1000; ++i )
		total += g( variables, sample, _max_value );

#if defined CHRONO
	if( first )
	{
		auto end = std::chrono::steady_clock::now();
		cerr << "Obj_MO::required_cost: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs\n";
		first = false;
	}
#endif
	
	return total;
}
