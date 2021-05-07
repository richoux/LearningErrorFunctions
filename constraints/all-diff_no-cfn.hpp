#pragma once

#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "all-diff_concept.hpp"

using namespace std;
using namespace ghost;

class AllDiff : public Constraint
{
	AllDiffConcept _ad_concept_;
	
	double required_error( const vector< Variable >& variables ) const override;

public:
	AllDiff( const vector< Variable >& variables );
};
