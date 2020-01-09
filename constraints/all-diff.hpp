#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "all-diff_concept.hpp"

using namespace std;
using namespace ghost;

class AllDiff : public Constraint
{
	vector<int> _weights;
	AllDiffConcept _ad_concept;
	
	double required_cost() const override;

public:
	AllDiff( const vector< reference_wrapper<Variable> >& variables );
};
