#pragma once

#include <vector>
#include <functional>
#include <map>
#include <string>

#include <ghost/variable.hpp>
#include <ghost/objective.hpp>

#include "../utils/randutils.hpp"
#include "../constraints/concept.hpp"

using namespace std;
using namespace ghost;

class Obj_hamming : public Objective
{
	unique_ptr<Concept> _concept;
	int _nb_vars;   
	vector<int> _random_sol;
	vector<int> _random_config;
	map<string, double> _cost_map;
	
	mutable randutils::mt19937_rng _rng;

	double required_cost( const vector< Variable >& ) const override;
	
public:
	Obj_hamming( unique_ptr<Concept>, int, const vector<int>&, const vector<int>& );
};
