#include <algorithm>

#include "metrics.hpp"

/*
 * Local functions
 */

double manhattan_depth( const shared_ptr<Constraint> constraint,
                        const vector< Variable >& variables,
                        int depth )
{
	// Should never happen
	if( depth > variables.size() )
		return -1;

	
}


///////////////

double manhattan( const shared_ptr<Constraint> constraint,
                  const vector< reference_wrapper<Variable> >& variables )
{
	if( constraint.required_cost() == 0 )
		return 0;
	else	
	{
		return manhattan_depth( constraint, variables, 1 );
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

