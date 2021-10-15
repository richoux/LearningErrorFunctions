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
	string _input_file_path;
	int _nb_vars;
	vector<int> _random_solutions;
	vector<int> _random_configurations;
	map<string, pair<double,double>> _cost_map;

public:
	Fitness( const vector<Variable>& variables,
	         const string& input_file_path,
	         const vector<int>& random_solutions,
	         const vector<int>& random_configurations );
	double required_cost( const vector<Variable*>& variables ) const override;
};
