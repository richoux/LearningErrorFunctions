#include <iostream>
#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../constraints/all-diff_hardcoded.hpp"

using namespace std;
using namespace ghost;

int main()
{
	vector< Variable > vars;
	for( int i = 0; i < 4; ++i )
		vars.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 1, 4 );

	vector< reference_wrapper<Variable> > vars_ref( vars.begin(), vars.end() );

	AllDiff ad( vars_ref );

	vars[0].set_value( 2 );
	vars[1].set_value( 1 );
	vars[2].set_value( 2 );
	vars[3].set_value( 2 );
	cout << "cost for (2,1,2,2) should be 2: " << ad.cost() << "\n";

	vars[1].set_value( 2 );
	cout << "cost for (2,2,2,2) should be 3: " << ad.cost() << "\n";

	vars[2].set_value( 4 );
	vars[3].set_value( 4 );
	cout << "cost for (2,2,4,4) should be 2: " << ad.cost() << "\n";

	vars[1].set_value( 1 );
	cout << "cost for (2,1,4,4) should be 1: " << ad.cost() << "\n";

	vars[2].set_value( 3 );
	cout << "cost for (2,1,3,4) should be 0: " << ad.cost() << "\n";
}
