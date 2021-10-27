#pragma once

#include <memory>
#include <ghost/model_builder.hpp>

#if defined HANDMADE
#include "../../constraints/linear-eq_handmade.hpp"
#elif defined FASTFORWARD
#include "../../constraints/linear-eq.hpp"
#elif defined HARDCODED
#include "../../constraints/linear-eq_hardcoded.hpp"
#else
#include "../../constraints/linear-eq_no-cfn.hpp"
#endif

using namespace ghost;
using namespace std;

class Builder : public ModelBuilder
{
	int _instance_size;
	int _nb_vars;
	int _constant;
	vector< vector<int> > _rows;
  vector< vector<int> > _columns;
  vector< vector<int> > _diagonals;

public:
	Builder( int instance_size );
	
	void declare_variables() override;
	void declare_constraints() override;
};
