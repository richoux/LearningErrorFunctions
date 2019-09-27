#include <iostream>
#include <vector>

using namespace std;

vector<double> interpreter( int number, const vector<double>& inputs );
vector<double> compute( int LIO, const vector<double>& inputs, const vector<int>& weights );

void print( const vector<double>& outputs )
{
	for( auto o : outputs )
		cout << o << " ";
	cout << "\n";
}
	
int main()
{
	vector<double> inputs{0.0, 0.1, -0.1, 0.5, -0.5, 1.0, -1.0, 2.0, -2.0, 5.0, -5.0, 10.0, -10.0 };

	vector<double> outputs;
	vector<int> weights{0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0,0,0,0};

	cout << "gaussian(x)\n";
	outputs = compute( 16, inputs, weights );
	auto gogoss = interpreter( 6, inputs );
	auto tatan = interpreter( 3, inputs );
	
	print( outputs );
	print( gogoss );

	cout << "\ntanh(x)\n";
	outputs = compute( 13, inputs, weights );
	print( outputs );
	print( tatan );

	cout << "\nsin( gaussian(x) + tanh(x) )\n";
	outputs = compute( 22, inputs, weights );
	vector<double>poupoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute[i] = tatan[i] + gogoss[i]; 
			
	auto poupoute0 = interpreter( 2, poupoute );
	
	print( outputs );
	print( poupoute0 );

	cout << "\nsigmoid( gaussian(x) + tanh(x) )\n";
	outputs = compute( 25, inputs, weights );
	auto poupoute1 = interpreter( 5, poupoute );
	
	print( outputs );
	print( poupoute1 );

	cout << "\ngaussian( gaussian(x) + tanh(x) )\n";
	outputs = compute( 26, inputs, weights );
	auto poupoute2 = interpreter( 6, poupoute );
	
	print( outputs );
	print( poupoute2 );

	cout << "\nsin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) )\n";
	outputs = compute( 30, inputs, weights );
	vector<double>poupoute_moumoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute_moumoute[i] = poupoute0[i] + poupoute1[i] + poupoute2[i]; 
			
	auto poupoute_supreme = interpreter( 0, poupoute_moumoute );
	
	print( outputs );
	print( poupoute_supreme );

	cout << "\nFAKE tanh( sin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) ) )\n";
	outputs = compute( 33, inputs, weights );
	print( outputs );
	
	return EXIT_SUCCESS;
}
