#include <random>
#include <cmath>
#include <algorithm>

#include <iterator>

#include "obj_hamming.hpp"
#include "function_to_learn_cppn.hpp"
#include "../utils/convert.hpp"

Obj_hamming::Obj_hamming( unique_ptr<Concept> concept,
                          int nb_vars,
                          const vector<int>& random_solutions,
                          const vector<int>& samples,
                          const map<string, double>& cost_map )
	: Objective( "Min difference with the Hamming distance" ),
	  _concept( std::move( concept ) ),
	  _nb_vars( nb_vars ),
	  _random_sol( random_solutions ),
	  _random_config( samples ),
	  _cost_map( cost_map )
{ }

double Obj_hamming::required_cost( const vector< Variable >& variables ) const
{

}
