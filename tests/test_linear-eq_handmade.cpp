#include <iostream>
#include <vector>

#include <ghost/variable.hpp>
#include <ghost/constraint.hpp>

#include "../constraints/linear-eq_handmade.hpp"

using namespace std;
using namespace ghost;

int main()
{
	vector< Variable > vars;
	for( int i = 0; i < 4; ++i )
		vars.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 9 );

	vector< reference_wrapper<Variable> > vars_ref( vars.begin(), vars.end() );

	LinearEq le( vars_ref, 8, 27 );

	vars[0].set_value( 8 );
	vars[1].set_value( 7 );
	vars[2].set_value( 5 );
	vars[3].set_value( 3 );
	cout << "cost for (9,8,6,4) should be 0: " << le.cost() << "\n";

	vars[3].set_value( 2 );
	cout << "cost for (9,8,6,3) should be 1.near_0: " << le.cost() << "\n";

	vars[2].set_value( 0 );
	vars[3].set_value( 0 );
	cout << "cost for (9,8,1,1) should be 1.near_3: " << le.cost() << "\n";

	vars[1].set_value( 0 );
	cout << "cost for (9,1,1,1) should be 2.near_6: " << le.cost() << "\n";

	vars[0].set_value( 0 );
	cout << "cost for (1,1,1,1) should be 3.9: " << le.cost() << "\n";
}
