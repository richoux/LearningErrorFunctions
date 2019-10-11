#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

using namespace std;
using namespace ghost;

class Concept : public Constraint
{
	mutable vector<int> _weights;

	double required_cost() const override;

protected:
	int nb_vars;
	int max_domain;
	double max_cost;
	
	//bool concept() const;
public:
	Concept( const vector< reference_wrapper<Variable> >& variables, const vector<int>& weights );
	
	virtual bool concept( const vector<int>& var ) const = 0;
	virtual bool concept( const vector< reference_wrapper<Variable> >& var ) const = 0;
};
