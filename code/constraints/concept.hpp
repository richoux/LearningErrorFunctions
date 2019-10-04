#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Concept : public Constraint
{
	double required_cost() const override;

protected:
	int nb_vars;
	int max_domain;
	double max_cost;
	vector<int> weights;
	
	bool concept() const;
public:
	Concept( const vector< reference_wrapper<Variable> >& variables );
	
	virtual bool concept( const vector<int>& var ) const = 0;
};
