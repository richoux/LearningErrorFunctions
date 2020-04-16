#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>
#include <random>

#include "../learn/function_to_learn_icn.hpp"
#include "../utils/convert.hpp"

#include "../utils/randutils.hpp"

using namespace std;

// in function_to_learn_icn.cpp
void interpreter_transformation( int number, const vector<double>& inputs, vector<double>& outputs );
void interpreter_comparison( int number, const vector<double>& inputs, vector<double>& outputs, double parameter );
void interpreter_comparison( int number, const vector<double>& inputs, vector<double>& outputs, double parameter_1, double parameter_2 );
void transformation_layer( const vector<double>& inputs, vector<double>& outputs, int nb_vars, int nb_params, const vector<int>& weights );
int comparison_layer( const vector<double>& inputs, vector<double>& outputs, int nb_vars, int nb_params, const vector<int>& weights, double parameter_1, double parameter_2 );
double intermediate_g( const vector<int>& weights, const vector<double>& inputs, int nb_vars, int nb_params, double parameter_1, double parameter_2 );

int main()
{
	randutils::mt19937_rng rng;
	
	vector<double> config( 9 );
	// std::iota( config.begin(), config.end(), 1.0 );
	// cout << "Config: ";
	// std::copy( config.begin(), config.end(), std::ostream_iterator<double>( cout, " " ) );

	// equals + less than
	vector<int> raw_weights{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 };
	//vector<int> raw_weights{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 };

	cout << "\nRaw weights: ";
	std::copy( raw_weights.begin(), raw_weights.end(), std::ostream_iterator<int>( cout, " " ) );

	auto weights = make_weights( raw_weights );

	auto recover_weights = recover_raw_weights( weights );
	cout << "\nRecover weights: ";
	std::copy( recover_weights.begin(), recover_weights.end(), std::ostream_iterator<int>( cout, " " ) );

	cout << "\nWeights: ";
	std::copy( weights.begin(), weights.end(), std::ostream_iterator<int>( cout, " " ) );

	// vector<double> outputs_transfo( 9 * number_units_transfo );
	// transformation_layer( config, outputs_transfo, 9, 1, weights );

	// cout << "\nOutput Transfo: ";
	// std::copy( outputs_transfo.begin(), outputs_transfo.end(), std::ostream_iterator<double>( cout, " " ) );

	// auto cost = g( weights, config, 0, (int)config.size() );
	// cout << "\nCost: " <<  cost << "\n";
	
	// rng.shuffle(config);
	// cout << "\nConfig: ";
	// std::copy( config.begin(), config.end(), std::ostream_iterator<double>( cout, " " ) );
	// cost = g( weights, config, 0, (int)config.size() );
	// cout << "\nCost: " <<  cost << "\n";

	// rng.shuffle(config);
	// cout << "\nConfig: ";
	// std::copy( config.begin(), config.end(), std::ostream_iterator<double>( cout, " " ) );
	// cost = g( weights, config, 0, (int)config.size() );
	// cout << "\nCost: " <<  cost << "\n";

	// vector<int> new_config( 9 );
	// rng.generate<std::uniform_int_distribution>( new_config, 1, 9 );
	// vector<double> new_config_d( new_config.begin(), new_config.end() );	
	
	// cout << "\nNew config: ";
	// std::copy( new_config_d.begin(), new_config_d.end(), std::ostream_iterator<double>( cout, " " ) );
	// cost = g( weights, new_config_d, 0, (int)new_config_d.size() );
	// cout << "\nCost: " <<  cost << "\n";

	// rng.shuffle(new_config_d);
	// cout << "\nNew config: ";
	// std::copy( new_config_d.begin(), new_config_d.end(), std::ostream_iterator<double>( cout, " " ) );
	// cost = g( weights, new_config_d, 0, (int)new_config_d.size() );
	// cout << "\nCost: " <<  cost << "\n";

	double cost;
	vector<int> new_config( 9 );
	for( int i = 0; i < 10; ++i )
	{
		rng.generate<std::uniform_int_distribution>( new_config, 1, 9 );
		std::copy( new_config.begin(), new_config.end(), config.begin() );
		cout << "\nConfig: ";
		std::copy( config.begin(), config.end(), std::ostream_iterator<double>( cout, " " ) );
		cost = g( weights, config, 0, (int)config.size() );
		cout << "\nCost: " <<  cost << "\n";
	}

	std::fill( raw_weights.begin(), raw_weights.end(), 0 );
	weights = make_weights( raw_weights );
	rng.generate<std::uniform_int_distribution>( new_config, 1, 9 );
	std::copy( new_config.begin(), new_config.end(), config.begin() );
	cout << "\nConfig: ";
	std::copy( config.begin(), config.end(), std::ostream_iterator<double>( cout, " " ) );
	cost = g( weights, config, 0, (int)config.size() );
	cout << "\nCost (should be max): " <<  cost << "\n";
		
	return EXIT_SUCCESS;
}
