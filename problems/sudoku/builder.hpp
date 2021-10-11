#pragma once

#include <memory>
#include <ghost/model_builder.hpp>

#if defined HANDMADE
#include "../../constraints/all-diff_handmade.hpp"
#elif defined NOCFN
#include "../../constraints/all-diff_no-cfn.hpp"
#elif defined HARDCODED
#include "../../constraints/all-diff_hardcoded.hpp"
#else
#include "../../constraints/all-diff.hpp"
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

public:
	Builder( int instance_size );
	
	void declare_variables() override;
	void declare_constraints() override;
};
