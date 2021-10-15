#pragma once

#include <memory>
#include <ghost/model_builder.hpp>

using namespace ghost;
using namespace std;

class Builder : public ModelBuilder
{

public:
	Builder();
	
	void declare_variables() override;
	void declare_constraints() override;
	void declare_objective() override;
};
