#include "builder.hpp"
#include "at_least_one_neuron.hpp"
#include "mutual_exclusivity.hpp"
#include "conditional_parameter.hpp"
#include "fitness.hpp"

Builder::Builder( const map<string, pair<double,double>>& cost_map,
                  const vector<int>& random_solutions,
                  const vector<int>& random_configurations,
                  bool has_parameter,
                  int nb_vars,
                  int max_value,
                  const vector<double>& params )
	: ModelBuilder(),
	  _cost_map( cost_map ),
	  _random_solutions( random_solutions ),
	  _random_configurations( random_configurations ),
	  _has_parameter( has_parameter ),
	  _nb_vars( nb_vars ),
	  _max_value( max_value ),
	  _params( params )
{ }

void Builder::declare_variables()
{
	create_n_variables( 29, 0, 2 );
}

void Builder::declare_constraints()
{	
	constraints.emplace_back( make_shared<AtLeast>( std::vector<int>{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17} ) );
	constraints.emplace_back( make_shared<MutualExclusivity>( std::vector<int>{20,21,22,23,24,25,26,27,28} ) );
	constraints.emplace_back( make_shared<ConditionalParameter>( std::vector<int>{7,8,9,10,11,17,21,22,23,24}, _has_parameter ) );
}

void Builder::declare_objective()
{
	objective = make_shared<Fitness>( variables, _cost_map, _random_solutions, _random_configurations, _nb_vars, _max_value, _params );
}
