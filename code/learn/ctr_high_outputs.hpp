#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../utils/latin.hpp"
#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

class Ctr_HO : public Constraint
{
	int _nb_vars;
	int _max_value;
	vector<int> _random_configurations;
	map<string, double> _cost_map;
	mutable vector<int> _weights;
	mutable vector<double> _inputs;
	
	LHS _latin;
	mutable randutils::mt19937_rng _rng;
	
	double required_cost() const override;

public:
	Ctr_HO( const vector< reference_wrapper<Variable> >& weight_vars,
	        int nb_vars,
	        int max_value,
	        const vector<int>& random_configurations,
	        const map<string, double>& cost_map );
};
