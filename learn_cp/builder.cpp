#include "builder.hpp"

Builder::Builder()
	: ModelBuilder()
{ }

void Builder::declare_variables()
{
	create_n_variables( 29, 0, 2 );
}

void Builder::declare_constraints()
{
	constraints.emplace_back( make_shared<MutualExclusivity>( std::vector<int>{20,21,22,23,24,25,26,27,28} ) );
}

void Builder::declare_objective()
{
	objective = make_shared<Fitness>( variables );
}
