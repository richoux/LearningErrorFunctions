#include <vector>
#include <iostream>

#include "../latin/latin.hpp"

using namespace std;

int main()
{
	LHS latin;
	
	vector<int> samples = latin.sample( 9, 8 );

	for( int i = 0; i < (int)samples.size(); ++i )
	{
		if( i != 0 && i % 9 == 0 )
			cout << "\n";
		cout << samples[i] << " ";
	}

	cout << "\n";
	
	return EXIT_SUCCESS;
}
