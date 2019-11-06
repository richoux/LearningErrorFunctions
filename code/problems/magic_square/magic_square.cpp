#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cmath>

#include <ghost/solver.hpp>
#include <ghost/variable.hpp>

#if defined HANDMADE
#include "../../constraints/linear-eq_handmade.hpp"
#else
#include "../../constraints/linear-eq.hpp"
#endif

#include "../../constraints/linear-eq_concept.hpp"

using namespace ghost;
using namespace std;

void print_solution( const vector<int>& solution )
{
	int nb_vars = (int)solution.size();
	int order = static_cast<int>( std::sqrt( nb_vars ) );
	
	cout << "Solution:";
	
	for( int i = 0; i < nb_vars; ++i )
	{
		if( i%order == 0 )
			cout << "\n";
		
		cout << solution[i] << " ";
	}

	cout << "\n";
}

void check_solution( const vector<int>& solution, int constant )
{
	unique_ptr<Concept> le_concept = make_unique<LinearEqConcept>( constant );
	
	int nb_vars = (int)solution.size();
	int order = static_cast<int>( std::sqrt( nb_vars ) );
	
	vector<int> partial_sol( order );

	// Rows
	for( int i = 0; i < order; ++i )
	{
		std::copy( solution.begin() + ( i * order ),
		           solution.begin() + ( ( i + 1 ) * order ),
		           partial_sol.begin() );

		if( !le_concept->concept( partial_sol ) )
		{
			int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
			
			cout << "Problem in row " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "=> the sum is " << sum << " rather than " << constant << "\n";
		}
	}

	// Columns
	for( int i = 0; i < order; ++i )
	{
		for( int j = 0; j < order; ++j )
			partial_sol[j] = solution[ j * order + i ];

		if( !le_concept->concept( partial_sol ) )
		{
			int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );

			cout << "Problem in column " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "=> the sum is " << sum << " rather than " << constant << "\n";
		}
	}

	// Diagonal 0
	for( int i = 0; i < order; ++i )
		partial_sol[i] = solution[ i + ( i * order ) ];
		                           
	if( !le_concept->concept( partial_sol ) )
	{
		int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
		
		cout << "Problem in diagonal 0: ";
		std::copy( partial_sol.begin(),
		           partial_sol.end(),
		           std::ostream_iterator<int>( cout, " " ) );
		cout << "=> the sum is " << sum << " rather than " << constant << "\n";
	}

	// Diagonal 1
	for( int i = 0; i < order; ++i )
		partial_sol[i] = solution[ order - 1 - i + ( i * order ) ];
		                           
	if( !le_concept->concept( partial_sol ) )
	{
		int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
		
		cout << "Problem in diagonal 1: ";
		std::copy( partial_sol.begin(),
		           partial_sol.end(),
		           std::ostream_iterator<int>( cout, " " ) );
		cout << "=> the sum is " << sum << " rather than " << constant << "\n";
	}
}

///////////////////////

int main( int argc, char **argv )
{
	int order;
	if( argc == 1 )
		order = 3;
	else
		order = std::stoi( argv[1] );

	int nb_vars = order * order;
	int constant = order * ( nb_vars + 1 ) / 2;
	
  // Create variables, with domains starting from value 1
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 1, nb_vars );

  for( int i = 0; i < nb_vars; ++i )
	  variables[i].set_value( i + 1 );
	  
  vector< vector< reference_wrapper<Variable> > > rows( order );
  vector< vector< reference_wrapper<Variable> > > columns( order );
  vector< vector< reference_wrapper<Variable> > > diagonals( 2 );

  // Prepare row variables
  for( int row = 0; row < order; ++row )
	  std::copy_n( variables.begin() + ( row * order ),
	               order,
	               std::back_inserter( rows[ row ] ) );
  
  // Prepare column variables
  for( int col = 0; col < order; ++col )
	  for( int row = 0; row < order; ++row )
		  columns[ col ].push_back( variables[ col + ( row * order ) ] );
	  
  // Prepare square variables
  for( int row = 0; row < order; ++row )
  {
	  diagonals[ 0 ].push_back( variables[ row + ( row * order ) ] );
	  diagonals[ 1 ].push_back( variables[ order - 1 - row + ( row * order ) ] );
  }

  vector< shared_ptr< Constraint >> constraint_rows;
  vector< shared_ptr< Constraint >> constraint_columns;
  vector< shared_ptr< Constraint >> constraint_diagonals;

  // LinearEq
  for( int i = 0; i < order; ++i )
  {
	  constraint_rows.push_back( make_shared< LinearEq >( rows[i], nb_vars, constant ) );
	  constraint_columns.push_back( make_shared< LinearEq >( columns[i], nb_vars, constant ) );
  }
  constraint_diagonals.push_back( make_shared< LinearEq >( diagonals[0], nb_vars, constant ) );
  constraint_diagonals.push_back( make_shared< LinearEq >( diagonals[1], nb_vars, constant ) );

  vector< shared_ptr< Constraint >> constraints;

  std::move( constraint_rows.begin(),
             constraint_rows.end(),
             std::back_inserter( constraints ) );

  std::move( constraint_columns.begin(),
             constraint_columns.end(),
             std::back_inserter( constraints ) );

  std::move( constraint_diagonals.begin(),
             constraint_diagonals.end(),
             std::back_inserter( constraints ) );

  cout << "Constraint size: " << constraints.size() << "\n"
       << "Magic Square constant: " << constant << "\n";
  
  // true means it is a permutation problem
  Solver solver( variables, constraints, true );

  double cost = 0.;
	vector<int> solution( variables.size(), 0 );

	// 2min
	// solver.solve( cost, solution, 500000, 120000000 );

	// 30s
	// solver.solve( cost, solution, 1000000, 30000000 );
	
  // 5s
	solver.solve( cost, solution, 1000000, 5000000 );

	// 0.5s
	//solver.solve( cost, solution, 100000, 500000 );

	cout << "Cost: " << cost << "\n";
	print_solution( solution );
	check_solution( solution, constant );
	
  return EXIT_SUCCESS;
}

