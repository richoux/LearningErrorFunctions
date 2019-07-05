#include <iostream>
#include <vector>

#include "increment.hpp"

using namespace std;

void print( const vector<bool> &vec )
{
	for( auto b : vec )
		cout << b << " ";
	cout << "\n";
}

int main()
{
	vector<bool> vec{0,0,0,0};
	print( vec );

	for( int i = 0 ; i < 20 ; ++i )
	{
		increment_boolean_vector( vec );
		print( vec );
	}
}
