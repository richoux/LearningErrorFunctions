#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>

#include <ghost/solver.hpp>
#include <ghost/variable.hpp>
#include "all-diff.hpp"

using namespace ghost;
using namespace std;

int main( int argc, char **argv )
{
	int size_side_small_square = std::stoi( argv[1] );
	int size_side = size_side_small_square * size_side_small_square;
	int nb_vars = size_side * size_side;
  
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, size_side );

  for( auto& var : variables )
	  var.do_random_initialization();
  
  vector< vector< reference_wrapper<Variable> > > rows( size_side );
  vector< vector< reference_wrapper<Variable> > > columns( size_side );
  vector< vector< reference_wrapper<Variable> > > squares( size_side );

  // Prepare row variables
  for( int r = 0; r < size_side; ++r )
	  std::copy_n( variables.begin() + ( r * size_side ),
	               size_side,
	               std::back_inserter( rows[r] ) );
  
  // Prepare column variables
  for( int c = 0; c < size_side; ++c )
	  for( int line = 0; line < size_side; ++line )
		  columns[c].push_back( variables[ c + ( line * size_side ) ] );
	  
  // Prepare square variables
  for( int s_r = 0; s_r < size_side_small_square; ++s_r )
	  for( int s_c = 0; s_c < size_side_small_square; ++s_c )
		  for( int line = 0; line < size_side_small_square; ++line )
			  std::copy_n( variables.begin() + ( ( s_r * size_side * size_side_small_square )
			                                     + ( s_c * size_side_small_square )
			                                     + ( line * size_side ) ),
			               size_side_small_square,
			               std::back_inserter( squares[ ( s_r * size_side_small_square ) + s_c ] ) );

  
  vector< shared_ptr< Constraint >> constraint_rows;
  vector< shared_ptr< Constraint >> constraint_columns;
  vector< shared_ptr< Constraint >> constraint_squares;
  
  for( int i = 0; i < size_side; ++i )
  {
	  constraint_rows.push_back( make_shared< AllDiff >( rows[i] ) );
	  constraint_columns.push_back( make_shared< AllDiff >( columns[i] ) );
	  constraint_squares.push_back( make_shared< AllDiff >( squares[i] ) );
  }
  
  vector< shared_ptr< Constraint >> constraints;

  std::move( constraint_rows.begin(),
             constraint_rows.end(),
             std::back_inserter( constraints ) );

  std::move( constraint_columns.begin(),
             constraint_columns.end(),
             std::back_inserter( constraints ) );

  std::move( constraint_squares.begin(),
             constraint_squares.end(),
             std::back_inserter( constraints ) );

  Solver solver( variables, constraints );

  double cost = 0.;
	vector<int> solution( variables.size(), 0 );

	solver.solve( cost, solution, 30, 300 );

	cout << "Cost: " << cost << "\nSolution:";
	for( auto v : solution )
		cout << " " << v;
	cout << "\n";
	
  return EXIT_SUCCESS;
}

