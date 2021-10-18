#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <ghost/objective.hpp>

using namespace std;
using namespace ghost;

class Fitness : public Minimize
{
	vector<int> _random_solutions;
	vector<int> _random_configurations;
	map<string, pair<double,double>> _cost_map;
	int _nb_vars;
	int _max_value;
	vector<double> _params;

public:
	Fitness( const vector<Variable>& variables,
	         const map<string, pair<double,double>>& cost_map,
	         const vector<int>& random_solutions,
	         const vector<int>& random_configurations,
	         int nb_vars,
	         int max_value,
	         const vector<double>& params );
	
	double required_cost( const vector<Variable*>& variables ) const override;
};
