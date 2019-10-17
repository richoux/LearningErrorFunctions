#pragma once

#include <vector>
#include <functional>

#include <ghost/variable.hpp>
#include <ghost/objective.hpp>

#include "../utils/randutils.hpp"
#include "../constraints/concept.hpp"

using namespace std;
using namespace ghost;

class Obj_ECL : public Objective
{
	unique_ptr<Concept> _concept;
	int _nb_vars;   
	vector<int> _random_sol;
	vector<int> _random_config;
	vector<int> _walk;
	
	mutable randutils::mt19937_rng _rng;

	double required_cost( const vector< Variable >& ) const override;
	
public:
	Obj_ECL( unique_ptr<Concept>, int, const vector<int>&, const vector<int>& );
};
