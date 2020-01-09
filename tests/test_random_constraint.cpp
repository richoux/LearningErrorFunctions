#include <iostream>
#include <vector>

#include "../constraints/random_constraint_concept.hpp"

using namespace std;

int main()
{
	RandomConcept rc( 5, 5 );
	cout << rc.concept( {0,1,2,3,4}, 0, 5 ) << "\n"
	     << rc.concept( {1,1,1,1,1}, 0, 5 ) << "\n";
	
}
