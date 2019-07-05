#pragma once

#include <vector>
#include <functional>

#include "subghost/variable.hpp"

using namespace std;
using namespace ghost;


void print_csv( vector<reference_wrapper<Variable>> vec, double hamming, double manhattan, double mix )
{
	cout << hamming 
	     << "," << manhattan
	     << "," << mix;
	for( auto v : vec )
		cout << "," << v.get().get_value();
	cout << "\n";
}
