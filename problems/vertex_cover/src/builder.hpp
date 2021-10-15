#pragma once

#include <memory>
#include <ghost/model_builder.hpp>

// #if defined HANDMADE
// #include "../../constraints/linear-eq_handmade.hpp"
// #include "../../constraints/linear-leq_handmade.hpp"
#if defined FASTFORWARD
#include "../../constraints/linear-geq.hpp"
#include "../../constraints/linear-leq.hpp"
#elif defined HARDCODED
#include "../../constraints/linear-geq_hardcoded.hpp"
#include "../../constraints/linear-leq_hardcoded.hpp"
#else
#include "../../constraints/linear-geq_no-cfn.hpp"
#include "../../constraints/linear-leq_no-cfn.hpp"
#endif

using namespace ghost;
using namespace std;

class Builder : public ModelBuilder
{
	bool _large_instance;
	int _constant;
	std::vector<int> _all_variables;
	
public:
	Builder( int instance_size );
	
	void declare_variables() override;
	void declare_constraints() override;
};
