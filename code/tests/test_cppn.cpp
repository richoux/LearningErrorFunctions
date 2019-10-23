#include <iostream>
#include <vector>

#include <ghost/variable.hpp>

#include "../learn/function_to_learn_cppn.hpp"

using namespace std;
using namespace ghost;

// in function_to_learn_cppn.cpp
void interpreter( int number, const vector<double>& inputs, vector<double>& outputs );
void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& outputs );
double sigmoid( double x );

//////////////////

void print( const vector<double>& outputs )
{
	for( auto o : outputs )
		cout << o << " ";
	cout << "\n";
}
	
int main()
{
	// vector<double> inputs{0.0, 0.1, -0.1, 0.5, -0.5, 1.0, -1.0, 2.0, -2.0, 5.0, -5.0, 10.0, -10.0 };

	vector<double> inputs{1., 2., 3., 4., 5.};
	                   
	vector<double> outputs( inputs.size() );
	vector<int> weights{0,0,0,1,0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1};

	cout << "gaussian(x)\n";
	compute( 16, inputs, weights, outputs );
	vector<double> gogoss( inputs.size() );
	vector<double> tatan( inputs.size() );
	interpreter( 6, inputs, gogoss );
	interpreter( 3, inputs, tatan );
	
	print( outputs );
	print( gogoss );

	cout << "\ntanh(x)\n";
	compute( 13, inputs, weights, outputs );
	print( outputs );
	print( tatan );

	cout << "\nsin( gaussian(x) + tanh(x) )\n";
	compute( 22, inputs, weights, outputs );
	vector<double>poupoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute[i] = tatan[i] + gogoss[i]; 
			
	vector<double> poupoute0( inputs.size() );
	interpreter( 2, poupoute, poupoute0 );
	
	print( outputs );
	print( poupoute0 );

	cout << "\nsigmoid( gaussian(x) + tanh(x) )\n";
	compute( 25, inputs, weights, outputs );
	vector<double> poupoute1( inputs.size() );
	interpreter( 5, poupoute, poupoute1 );
	
	print( outputs );
	print( poupoute1 );

	cout << "\ngaussian( gaussian(x) + tanh(x) )\n";
	compute( 26, inputs, weights, outputs );
	vector<double> poupoute2( inputs.size() );
	interpreter( 6, poupoute, poupoute2 );
	
	print( outputs );
	print( poupoute2 );

	cout << "\nNORM( sin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) ) )\n";
	compute( 37, inputs, weights, outputs );
	vector<double>poupoute_moumoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute_moumoute[i] = poupoute0[i] + poupoute1[i] + poupoute2[i]; 
			
	vector<double> poupoute_supreme( inputs.size() );
	interpreter( 7, poupoute_moumoute, poupoute_supreme );
	
	print( outputs );
	print( poupoute_supreme );
	print( poupoute_moumoute );

	cout << "\nFAKE tanh( sin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) ) )\n";
	compute( 33, inputs, weights, outputs );
	print( outputs );

	///////////////////////////

	vector< Variable > weights_var; // be careful: variables of our problem actually represent weights
	for( int i = 0; i < number_functions * 3; ++i )
		weights_var.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 2 );

	// same as weigths, expect last layer - here id
	weights_var[3].set_value( 1 );
	weights_var[6].set_value( 1 );
	weights_var[10].set_value( 1 );
	weights_var[13].set_value( 1 );
	weights_var[14].set_value( 1 );
	// id
	weights_var[16].set_value( 1 );

	vector<int> config{1,2,3,4,5};
		
	cout << "\ncost g: " << g( weights_var, config ) << "\n";

	int nb_vars = (int)config.size();
	auto expected = (nb_vars + 0.9) * sigmoid( std::accumulate( poupoute_moumoute.begin(), poupoute_moumoute.end(), 0.0 ) / nb_vars );

	cout << "expeted cost: " << expected << "\n";
	
	return EXIT_SUCCESS;
}
