#pragma once

#include <vector>
#include <functional>

#include <ghost/variable.hpp>
#include <ghost/objective.hpp>

using namespace std;
using namespace ghost;

class Obj_ECL : public Objective
{
	double _length;
	int _nb_vars;
	int _max_value;
	
	double required_cost( const vector< Variable >& ) const override;
public:
	Obj_ECL( double, int, int );
};
