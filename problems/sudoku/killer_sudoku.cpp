#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>
#include <cmath>

#include <ghost/solver.hpp>
#include <ghost/variable.hpp>

#if defined HANDMADE
#include "../../constraints/all-diff_handmade.hpp"
#include "../../constraints/linear-eq_handmade.hpp"
#elif defined NOCFN
#include "../../constraints/all-diff_no-cfn.hpp"
#include "../../constraints/linear-eq_no-cfn.hpp"
#else
#include "../../constraints/all-diff.hpp"
#include "../../constraints/linear-eq.hpp"
#endif

#include "../../constraints/all-diff_concept.hpp"
#include "../../constraints/linear-eq_concept.hpp"

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
			cout << "   " << solution[i];
		else
			cout << " " << solution[i];
	}

	cout << "\n";

	for( int j = 0; j <= 2*size_side + size_side_small_square + 1; ++j )
		cout << "-";
	
	cout << "\n";
}

void check_solution( const vector<int>& solution,
                     const vector< vector< reference_wrapper<Variable> > >& cages,
                     const vector<int>& rhs_eq )
{
	unique_ptr<Concept> ad_concept = make_unique<AllDiffConcept>();
	vector< unique_ptr<Concept> > vec_le_concept( 29 );
	for( int i = 0; i < 29; ++i )
		vec_le_concept[i] = make_unique<LinearEqConcept>( rhs_eq[i] );
	
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
			// std::transform( partial_sol.begin(),
			//                 partial_sol.end(),
			//                 partial_sol.begin(),
			//                 [](auto p){ return p+1;});
			
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
				cout << "Problem in square (" << i+1 << "," << j+1 << "): ";
				std::copy( partial_sol.begin(),
				           partial_sol.end(),
				           std::ostream_iterator<int>( cout, " " ) );
				cout << "\n";
			}
		}

	// Cages
	for( int i = 0; i < 29; ++i )
	{
		vector<int> partial_cage( cages[i].size() );
		for( int j = 0; j < (int)cages[i].size(); ++j )
			partial_cage[j] = cages[i][j].get().get_value();
			
		if( !vec_le_concept[i]->concept( partial_cage ) )
		{
			std::transform( partial_cage.begin(),
			                partial_cage.end(),
			                partial_cage.begin(),
			                [](auto p){ return p+1;});

			int sum = accumulate( partial_cage.begin(), partial_cage.end(), 0 );
			
			cout << "Problem in cage " << i << ": sum of ";
			std::copy( partial_cage.begin(),
			           partial_cage.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "give " << sum << ", not " << rhs_eq[i] << "\n";
		}
	}
}

///////////////////////

int main( int argc, char **argv )
{
	int size_side_small_square = 3;
	int size_side = size_side_small_square * size_side_small_square;
	int nb_vars = size_side * size_side;
  
  // Create variables
  vector< Variable > variables;
  for( int i = 0; i < nb_vars; ++i )
		variables.emplace_back( std::string("v") + std::to_string(i), std::string("v") + std::to_string(i), 1, size_side );

  for( int i = 0; i < nb_vars; ++i )
	  variables[i].set_value( ( i % size_side ) + 1 );
	  
  vector< vector< reference_wrapper<Variable> > > rows( size_side );
  vector< vector< reference_wrapper<Variable> > > columns( size_side );
  vector< vector< reference_wrapper<Variable> > > squares( size_side );
  vector< vector< reference_wrapper<Variable> > > cages( 29 );

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

  // Prepare cages variables: problem instance from http://www.csplib.org/Problems/prob057/
  // cage_0 = 3
  cages[0].push_back( variables[ 0 ] );
  cages[0].push_back( variables[ 1 ] );
  // cage_1 = 15
  cages[1].push_back( variables[ 2 ] );
  cages[1].push_back( variables[ 3 ] );
  cages[1].push_back( variables[ 4 ] );
  // cage_2 = 22
  cages[2].push_back( variables[ 5 ] );
  cages[2].push_back( variables[ 13 ] );
  cages[2].push_back( variables[ 14 ] );
  cages[2].push_back( variables[ 22 ] );
  // cage_3 = 4
  cages[3].push_back( variables[ 6 ] );
  cages[3].push_back( variables[ 15 ] );
  // cage_4 = 16
  cages[4].push_back( variables[ 7 ] );
  cages[4].push_back( variables[ 16 ] );
  // cage_5 = 15
  cages[5].push_back( variables[ 8 ] );
  cages[5].push_back( variables[ 17 ] );
  cages[5].push_back( variables[ 26 ] );
  cages[5].push_back( variables[ 35 ] );
  // cage_6 = 25
  cages[6].push_back( variables[ 9 ] );
  cages[6].push_back( variables[ 10 ] );
  cages[6].push_back( variables[ 18 ] );
  cages[6].push_back( variables[ 19 ] );
  // cage_7 = 17
  cages[7].push_back( variables[ 11 ] );
  cages[7].push_back( variables[ 12 ] );
  // cage_8 = 9
  cages[8].push_back( variables[ 20 ] );
  cages[8].push_back( variables[ 21 ] );
  cages[8].push_back( variables[ 30 ] );
  // cage_9 = 8
  cages[9].push_back( variables[ 23 ] );
  cages[9].push_back( variables[ 32 ] );
  cages[9].push_back( variables[ 41 ] );
  // cage_10 = 20
  cages[10].push_back( variables[ 24 ] );
  cages[10].push_back( variables[ 25 ] );
  cages[10].push_back( variables[ 33 ] );
  // cage_11 = 6
  cages[11].push_back( variables[ 27 ] );
  cages[11].push_back( variables[ 36 ] );
  // cage_12 = 14
  cages[12].push_back( variables[ 28 ] );
  cages[12].push_back( variables[ 29 ] );
  // cage_13 = 17
  cages[13].push_back( variables[ 31 ] );
  cages[13].push_back( variables[ 40 ] );
  cages[13].push_back( variables[ 49 ] );
  // cage_14 = 17
  cages[14].push_back( variables[ 34 ] );
  cages[14].push_back( variables[ 42 ] );
  cages[14].push_back( variables[ 43 ] );
  // cage_15 = 13
  cages[15].push_back( variables[ 37 ] );
  cages[15].push_back( variables[ 38 ] );
  cages[15].push_back( variables[ 46 ] );
  // cage_16 = 20
  cages[16].push_back( variables[ 39 ] );
  cages[16].push_back( variables[ 48 ] );
  cages[16].push_back( variables[ 57 ] );
  // cage_17 = 12
  cages[17].push_back( variables[ 44 ] );
  cages[17].push_back( variables[ 53 ] );
  // cage_18 = 27
  cages[18].push_back( variables[ 45 ] );
  cages[18].push_back( variables[ 54 ] );
  cages[18].push_back( variables[ 63 ] );
  cages[18].push_back( variables[ 72 ] );
  // cage_19 = 6
  cages[19].push_back( variables[ 47 ] );
  cages[19].push_back( variables[ 55 ] );
  cages[19].push_back( variables[ 56 ] );
  // cage_20 = 20
  cages[20].push_back( variables[ 50 ] );
  cages[20].push_back( variables[ 59 ] );
  cages[20].push_back( variables[ 60 ] );
  // cage_21 = 6
  cages[21].push_back( variables[ 51 ] );
  cages[21].push_back( variables[ 52 ] );
  // cage_22 = 10
  cages[22].push_back( variables[ 58 ] );
  cages[22].push_back( variables[ 66 ] );
  cages[22].push_back( variables[ 67 ] );
  cages[22].push_back( variables[ 75 ] );
  // cage_23 = 14
  cages[23].push_back( variables[ 61 ] );
  cages[23].push_back( variables[ 62 ] );
  cages[23].push_back( variables[ 70 ] );
  cages[23].push_back( variables[ 71 ] );
  // cage_24 = 8
  cages[24].push_back( variables[ 64 ] );
  cages[24].push_back( variables[ 73 ] );
  // cage_25 = 16
  cages[25].push_back( variables[ 65 ] );
  cages[25].push_back( variables[ 74 ] );
  // cage_26 = 15
  cages[26].push_back( variables[ 68 ] );
  cages[26].push_back( variables[ 69 ] );
  // cage_27 = 13
  cages[27].push_back( variables[ 76 ] );
  cages[27].push_back( variables[ 77 ] );
  cages[27].push_back( variables[ 78 ] );
  // cage_28 = 17
  cages[28].push_back( variables[ 79 ] );
  cages[28].push_back( variables[ 80 ] );

  
  vector< shared_ptr< Constraint >> constraint_rows;
  vector< shared_ptr< Constraint >> constraint_columns;
  vector< shared_ptr< Constraint >> constraint_squares;
  vector< shared_ptr< Constraint >> constraint_cages;

  // AllDiff
  for( int i = 0; i < size_side; ++i )
  {
	  constraint_rows.push_back( make_shared< AllDiff >( rows[i] ) );
	  constraint_columns.push_back( make_shared< AllDiff >( columns[i] ) );
	  constraint_squares.push_back( make_shared< AllDiff >( squares[i] ) );
  }

  // LinearEq
  // max_value = size_side - 1
  vector<int> rhs_eq{ 3, 15, 22, 4, 16, 15, 25, 17, 9, 8, 20, 6, 14, 17, 17, 13, 20, 12, 27, 6, 20, 6, 10, 14, 8, 16, 15, 13, 17 };
  for( int i = 0; i < 29; ++i )
	  constraint_cages.push_back( make_shared< LinearEq >( cages[i], size_side - 1, rhs_eq[i] ) );
  
  // constraint_cages.push_back( make_shared< LinearEq >( cages[0], 3 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[1], 15 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[2], 22 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[3], 4 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[4], 16 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[5], 15 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[6], 25 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[7], 17 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[8], 9 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[9], 8 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[10], 20 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[11], 6 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[12], 14 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[13], 17 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[14], 17 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[15], 13 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[16], 20 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[17], 12 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[18], 27 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[19], 6 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[20], 20 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[21], 6 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[22], 10 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[23], 14 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[24], 8 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[25], 16 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[26], 15 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[27], 13 ) );
  // constraint_cages.push_back( make_shared< LinearEq >( cages[28], 17 ) );
  

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

  std::move( constraint_cages.begin(),
             constraint_cages.end(),
             std::back_inserter( constraints ) );

  //cout << "Constraint size: " << constraints.size() << "\n";
  
  // true means it is a permutation problem
  Solver solver( variables, constraints, true );

  double cost = 0.;
	vector<int> solution( variables.size(), 0 );

	// 2min
	// solver.solve( cost, solution, 500000, 120000000 );

	// 30s
	// solver.solve( cost, solution, 1000000, 30000000 );
	
  // 10
	solver.solve( cost, solution, 100000, 10000000 );

	// 0.5s
	//solver.solve( cost, solution, 100000, 500000 );

	cout << "Cost: " << cost << "\n";
	print_solution( solution );
	check_solution( solution, cages, rhs_eq );
	
  return EXIT_SUCCESS;
}

