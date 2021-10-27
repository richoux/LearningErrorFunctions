#pragma once

#include <sstream>
#include <vector>

#include "ghost/print.hpp"
#include "ghost/variable.hpp"

using namespace std;
using namespace ghost;

class PrintICN : public Print
{
public:
	stringstream print_candidate( const std::vector<Variable>& variables ) const override;
};
