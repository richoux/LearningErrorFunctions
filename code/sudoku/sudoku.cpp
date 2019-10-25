#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cmath>

#include <ghost/solver.hpp>
#include <ghost/variable.hpp>
#include "../constraints/all-diff.hpp"
#include "../constraints/all-diff_concept.hpp"

using namespace ghost;
using namespace std;

void print_solution( const vector<int>& solution )
{
	int nb_vars = solution.size();
	int size_side = static_cast<int>( std::sqrt( nb_vars ) );
	int size_side_small_square = static_cast<int>( std::sqrt( size_side ) );
	
	cout << "Solution:";
	
	for( int i = 0; i < nb_vars; ++i )
	{
		if( i%size_side == 0 )
		{
			cout << "\n";

			if( ( i/size_side) % size_side_small_square == 0 )
				for( int j = 0; j <= 2*size_side + size_side_small_square + 1; ++j )
					cout << "-";

			cout << "\n";
		}

		if( i%size_side_small_square == 0 && i%size_side != 0)
				cout << "   " << solution[i] + 1;
		else
			cout << " " << solution[i] + 1;
	}

	cout << "\n";

	for( int j = 0; j <= 2*size_side + size_side_small_square + 1; ++j )
		cout << "-";
	
	cout << "\n";
}

void check_solution( const vector<int>& solution )
{
	//AllDiffConcept ad_concept;
	unique_ptr<Concept> ad_concept = make_unique<AllDiffConcept>();
	
	int nb_vars = solution.size();
	int size_side = static_cast<int>( std::sqrt( nb_vars ) );
	int size_side_small_square = static_cast<int>( std::sqrt( size_side ) );

	vector<int> partial_sol( size_side );

	// Rows
	for( int i = 0; i < size_side; ++i )
	{
		std::copy( solution.begin() + ( i * size_side ),
		           solution.begin() + ( ( i + 1 ) * size_side ),
		           partial_sol.begin() );

		if( !ad_concept->concept( partial_sol ) )
		{
			std::transform( partial_sol.begin(),
			                partial_sol.end(),
			                partial_sol.begin(),
			                [](auto p){ return p+1;});
			
			cout << "Problem in row " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "\n";
		}
	}

	// Columns
	for( int i = 0; i < size_side; ++i )
	{
		for( int j = 0; j < size_side; ++j )
			partial_sol[j] = solution[ j * size_side + i ];

		if( !ad_concept->concept( partial_sol ) )
		{
			std::transform( partial_sol.begin(),
			                partial_sol.end(),
			                partial_sol.begin(),
			                [](auto p){ return p+1;});
			
			cout << "Problem in column " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "\n";
		}
	}

	// Squares
	for( int i = 0; i < size_side_small_square; ++i )
		for( int j = 0; j < size_side_small_square; ++j )
		{
			for( int k = 0; k < size_side_small_square; ++k )
				for( int l = 0; l < size_side_small_square; ++l )
				partial_sol[ k * size_side_small_square + l ] = solution[ i * ( size_side_small_square * size_side ) + j * size_side_small_square + k * size_side + l ];
			
			if( !ad_concept->concept( partial_sol ) )
			{
				std::transform( partial_sol.begin(),
				                partial_sol.end(),
				                partial_sol.begin(),
				                [](auto p){ return p+1;});
			
				cout << "Problem in square (" << i+1 << "," << j+1 << "): ";
				std::copy( partial_sol.begin(),
				           partial_sol.end(),
				           std::ostream_iterator<int>( cout, " " ) );
				cout << "\n";
			}
		}
}

///////////////////////

int main( int argc, char **argv )
{
	int size_side_small_square;
	if( argc == 1 )
		size_side_small_square = 3;
	else
		size_side_small_square = std::stoi( argv[1] );
	
	int size_side = size_side_small_square * size_side_small_square;
	int nb_vars = size_side * size_side;
  
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 0, size_side );

  for( int i = 0; i < nb_vars; ++i )
	  variables[i].set_value( i % size_side );
	  
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
	  //cout << rows[i].size() << " " << columns[i].size() << " " << squares[i].size() << "\n";
	  // for( auto& v : rows[i] )
		//   cout << v.get().get_name() << " ";
	  // cout << "\n";
	  
	  // for( auto& v : columns[i] )
		//   cout << v.get().get_name() << " ";
	  // cout << "\n";

	  // for( auto& v : squares[i] )
		//   cout << v.get().get_name() << " ";
	  // cout << "\n";

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

  cout << "Constraint size: " << constraints.size() << "\n";
  
  // true means it is a permutation problem
  Solver solver( variables, constraints, true );

  double cost = 0.;
	vector<int> solution( variables.size(), 0 );

	// 30s
	//try
	//{
		solver.solve( cost, solution, 1000000, 30000000 );
	// }
	// catch( exception& e )
	// {
	// 	cout << "NAN EXCEP!\n";
	// 	print_solution( solution );
	// }
	
  // 5s
	//solver.solve( cost, solution, 1000000, 5000000 );

	// 0.5s
	//solver.solve( cost, solution, 100000, 500000 );

	cout << "Cost: " << cost << "\n";
	print_solution( solution );
	check_solution( solution );
	
  return EXIT_SUCCESS;
}

