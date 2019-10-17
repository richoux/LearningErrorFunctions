#include <iostream>

#include <random>
#include <cmath>

#include "../latin/latin.hpp"
#include "random_draw.hpp"

void random_draw( unique_ptr<Concept>& concept,
                  int nb_vars,
                  int max_value,
                  vector<int>& solutions,
                  vector<int>& not_solutions,
                  double percent )
{
	LHS latin;
	int value_size = max_value + 1;
  vector<int> configuration( nb_vars );
  unsigned long long int sampling_size = static_cast<unsigned long long int>( percent * std::pow( max_value + 1, nb_vars ) / 100 );
  vector<int> latin_draws = latin.sample( nb_vars, max_value );

  for( unsigned long long int i = 0; i < sampling_size; i += value_size )
  {
	  for( int j = 0; j < value_size; ++j )
		  if( concept->concept( latin_draws, j * nb_vars, (j + 1) * nb_vars ) )
		  {
			  //++counter;
			  solutions.insert( solutions.end(),
			                    latin_draws.begin() + ( j * nb_vars ),
			                    latin_draws.begin() + ( ( j + 1 ) * nb_vars ) );
		  }
		  else
			  not_solutions.insert( not_solutions.end(),
			                        latin_draws.begin() + ( j * nb_vars ),
			                        latin_draws.begin() + ( ( j + 1 ) * nb_vars ) );
	  
	  latin_draws = latin.sample( nb_vars, max_value );
  }
}
