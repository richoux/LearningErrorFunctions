#include <iostream>
#include <vector>

#include <ghost/variable.hpp>

#include "../learn/function_to_learn_cppn.hpp"

using namespace std;
using namespace ghost;

// in function_to_learn_cppn.cpp
void interpreter( int number, const vector<double>& inputs, vector<double>& outputs, int );
void compute( int LO, const vector<double>& inputs, const vector<int>& weights, vector<double>& outputs, int );
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

	vector<double> inputs{0., 1., 2., 3., 4.};
	                   
	vector<double> outputs( inputs.size() );
	vector<int> weights{0,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0,0,0,0};

	vector<int> weights_norm{1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0};
	vector<int> weights_norm_tanh{0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0};

	cout << "norm_01(x)\n";
	compute( 10, inputs, weights_norm, outputs, 4 );
	vector<double> nonorm( inputs.size() );
	interpreter( 0, inputs, nonorm, 4 );
	
	print( outputs );
	print( nonorm );

	cout << "\nnorm_-11(x)\n";
	compute( 11, inputs, weights_norm, outputs, 4 );
	interpreter( 1, inputs, nonorm, 4 );
	
	print( outputs );
	print( nonorm );

	cout << "\ngaussian(x)\n";
	compute( 16, inputs, weights, outputs, 4 );
	vector<double> gogoss( inputs.size() );
	interpreter( 6, inputs, gogoss, 4 );
	
	print( outputs );
	print( gogoss );

	cout << "\ntanh(x)\n";
	compute( 13, inputs, weights, outputs, 4 );
	vector<double> tatan( inputs.size() );
	interpreter( 3, inputs, tatan, 4 );

	print( outputs );
	print( tatan );

	cout << "\nnorm_01( tanh(x) )\n";
	compute( 20, inputs, weights_norm_tanh, outputs, 4 );
	interpreter( 0, tatan, nonorm, 4 );
	
	print( outputs );
	print( nonorm );

	cout << "\nnorm_-11(( tanh(x) )\n";
	compute( 21, inputs, weights_norm_tanh, outputs, 4 );
	interpreter( 1, tatan, nonorm, 4 );
	
	print( outputs );
	print( nonorm );

	cout << "\nsin( gaussian(x) + tanh(x) )\n";
	compute( 22, inputs, weights, outputs, 4 );
	vector<double>poupoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute[i] = tatan[i] + gogoss[i]; 
			
	vector<double> poupoute0( inputs.size() );
	interpreter( 2, poupoute, poupoute0, 4 );
	
	print( outputs );
	print( poupoute0 );

	cout << "\nsigmoid( gaussian(x) + tanh(x) )\n";
	compute( 25, inputs, weights, outputs, 4 );
	vector<double> poupoute1( inputs.size() );
	interpreter( 5, poupoute, poupoute1, 4 );
	
	print( outputs );
	print( poupoute1 );

	cout << "\ngaussian( gaussian(x) + tanh(x) )\n";
	compute( 26, inputs, weights, outputs, 4 );
	vector<double> poupoute2( inputs.size() );
	interpreter( 6, poupoute, poupoute2, 4 );
	
	print( outputs );
	print( poupoute2 );

	cout << "\nnorm_01( sin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) ) )\n";
	compute( 30, inputs, weights, outputs, 4 );
	vector<double>poupoute_moumoute( inputs.size() );
	for( int i = 0; i < inputs.size(); ++i )
		poupoute_moumoute[i] = poupoute0[i] + poupoute1[i] + poupoute2[i]; 
			
	vector<double> poupoute_supreme( inputs.size() );
	interpreter( 0, poupoute_moumoute, poupoute_supreme, 4 );
	
	print( outputs );
	print( poupoute_supreme );
	print( poupoute_moumoute );

	cout << "\nFAKE tanh( sin( gaussian(x) + tanh(x) ) + sigmoid( gaussian(x) + tanh(x) ) + gaussian( gaussian(x) + tanh(x) ) )\n";
	compute( 33, inputs, weights, outputs, 4 );
	print( outputs );

	///////////////////////////

	vector< Variable > weights_var; // be careful: variables of our problem actually represent weights
	for( int i = 0; i < number_functions * 3; ++i )
		weights_var.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, 2 );

	// same as weigths, expect last layer - here id
	weights_var[3].set_value( 1 );
	weights_var[6].set_value( 1 );
	weights_var[9].set_value( 1 );
	weights_var[12].set_value( 1 );
	weights_var[13].set_value( 1 );
	weights_var[14].set_value( 1 );

	vector<int> config{0,1,2,3,4};

	cout << "\ncost g: " << g( weights_var, config, 4 ) << "\n";

	int nb_vars = (int)config.size();
	auto expected = (nb_vars + 0.9) * sigmoid( std::accumulate( poupoute_supreme.begin(), poupoute_supreme.end(), 0.0 ) / nb_vars );

	cout << "expeted cost: " << expected << "\n";

	weights_var[4].set_value( 1 );
	weights_var[6].set_value( 0 );
	weights_var[9].set_value( 0 );
	weights_var[10].set_value( 1 );
	weights_var[11].set_value( 1 );
	weights_var[12].set_value( 0 );
	weights_var[13].set_value( 0 );

	//vector<int> config2{6, 6, 6, 4, 5, 4, 1, 1, 1};
	vector<int> config2{4, 4, 4, 4, 4, 4, 4, 4, 4};
	cout << "\nNaN g? " << g( weights_var, config2, 8 ) << "\n";
	
	
	return EXIT_SUCCESS;
}
