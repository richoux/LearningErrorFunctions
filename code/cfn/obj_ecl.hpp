#pragma once

#include <vector>
#include <functional>

#include <ghost/variable.hpp>
#include <ghost/objective.hpp>

using namespace std;
using namespace ghost;

class Obj_ECL : public Objective
{
	int _length; // random walk length
	int _nb_vars;   
	int _max_value; // max value in variables' domain (we assume it is the same for each variable)
	
	double required_cost( const vector< Variable >& ) const override;
public:
	Obj_ECL( int, int, int );
};
