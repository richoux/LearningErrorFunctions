#include <vector>
#include <iostream>
#include <string>

#include "../utils/convert.hpp"

using namespace std;

int main( int argc, char **argv )
{
	vector<int> vec{ 3, 10, 9, 7, 7, 3, 5 };
	cout << convert( vec ) << "\n";
	return EXIT_SUCCESS;
}
