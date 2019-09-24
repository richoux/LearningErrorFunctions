#pragma once

#include <vector>
#include <functional>

#include <ghost/variable.hpp>
#include <ghost/objective.hpp>

#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

class Obj_ECL : public Objective
{
	int _nb_vars;   
	int _max_value; // max value in variables' domain (we assume it is the same for each variable)
	//vector< vector<int> > _random_sol;
	//vector<int> _random_sol;
	//mutable vector<int> _index;
	vector<int> _samples;
	
	mutable randutils::mt19937_rng _rng;

	double required_cost( const vector< Variable >& ) const override;
	
public:
	//Obj_ECL( int, int, const vector< vector<int> >& );
	Obj_ECL( int, int, const vector<int>& );
};
