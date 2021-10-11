#pragma once

#include <memory>
#include <ghost/model.hpp>

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

class FactorySudoku : public FactoryModel
{
	int _instance_size;
	int _side_size;
	vector< vector<int> > _rows;
  vector< vector<int> > _columns;
  vector< vector<int> > _squares;

public:
	FactorySudoku( const std::vector<Variable>& variables, 
	               int instance_size );
	
	void declare_constraints() override;
};
