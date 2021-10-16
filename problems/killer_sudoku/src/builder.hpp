#pragma once

#include <memory>
#include <ghost/model_builder.hpp>

#if defined HANDMADE
#include "../../constraints/all-diff_handmade.hpp"
#include "../../constraints/linear-eq_hardcoded.hpp" // hardcoded = manhattan-fashion = correct one for handmade
#elif defined FASTFORWARD
#include "../../constraints/all-diff.hpp"
#include "../../constraints/linear-eq.hpp"
#elif defined HARDCODED
#include "../../constraints/all-diff_hardcoded.hpp"
#include "../../constraints/linear-eq_hardcoded.hpp"
#else
#include "../../constraints/all-diff_no-cfn.hpp"
#include "../../constraints/linear-eq_no-cfn.hpp"
#endif

using namespace ghost;
using namespace std;

class Builder : public ModelBuilder
{
	int _instance_size;
	int _side_size;
	int _nb_vars;
	vector< vector<int> > _rows;
  vector< vector<int> > _columns;
  vector< vector<int> > _squares;
  vector< vector<int> > _cages;

public:
	Builder( int instance_size );
	
	void declare_variables() override;
	void declare_constraints() override;
};
