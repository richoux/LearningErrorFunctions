#pragma once

#include <vector>
#include <random>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../latin/latin.hpp"
#include "../utils/randutils.hpp"

using namespace std;
using namespace ghost;

class Ctr_HO : public Constraint
{
	int _nb_vars;
	int _var_max_value;
	vector<int> _random_configurations;
	//vector< vector<int> > _random_configurations;
	map<string, double> _cost_map;
	mutable vector<int> _weights;
	mutable vector<double> _inputs;
	
	LHS _latin;
	mutable randutils::mt19937_rng _rng;
	
	double required_cost() const override;

public:
	Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, const vector<int>& random_configurations, const map<string, double>& cost_map );
	//Ctr_HO( const vector< reference_wrapper<Variable> >& coefficients, int nb_vars, int var_max_value, vector< vector<int> > random_configurations, map<string, double> cost_map );
};
