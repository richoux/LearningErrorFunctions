#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <utility>

#include <ghost/model_builder.hpp>

using namespace ghost;
using namespace std;

class Builder : public ModelBuilder
{
	map<string, pair<double,double>> _cost_map;
	vector<int> _random_solutions;
	vector<int> _random_configurations;
	bool _has_parameter;
	int _nb_vars;
	int _max_value;
	vector<double> _params;
	
public:
	Builder( const map<string, pair<double,double>>& cost_map,
	         const vector<int>& random_solutions,
	         const vector<int>& random_configurations,
	         bool has_parameter,
	         int nb_vars,
	         int max_value,
	         const vector<double>& params );
	
	void declare_variables() override;
	void declare_constraints() override;
	void declare_objective() override;
};
