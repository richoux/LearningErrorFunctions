#include <memory>
#include "../../constraints/all-diff_concept.hpp"
#include "../../constraints/linear-eq_concept.hpp"

void check_solution( const vector<int>& solution )
{
	vector< vector<int> > cages( 29 );
	// Prepare cages variables: problem instance from http://www.csplib.org/Problems/prob057/
  // cage_0 = 3
  cages[0].push_back( 0 );
  cages[0].push_back( 1 );
  // cage_1 = 15
  cages[1].push_back( 2 );
  cages[1].push_back( 3 );
  cages[1].push_back( 4 );
  // cage_2 = 22
  cages[2].push_back( 5 );
  cages[2].push_back( 13 );
  cages[2].push_back( 14 );
  cages[2].push_back( 22 );
  // cage_3 = 4
  cages[3].push_back( 6 );
  cages[3].push_back( 15 );
  // cage_4 = 16
  cages[4].push_back( 7 );
  cages[4].push_back( 16 );
  // cage_5 = 15
  cages[5].push_back( 8 );
  cages[5].push_back( 17 );
  cages[5].push_back( 26 );
  cages[5].push_back( 35 );
  // cage_6 = 25
  cages[6].push_back( 9 );
  cages[6].push_back( 10 );
  cages[6].push_back( 18 );
  cages[6].push_back( 19 );
  // cage_7 = 17
  cages[7].push_back( 11 );
  cages[7].push_back( 12 );
  // cage_8 = 9
  cages[8].push_back( 20 );
  cages[8].push_back( 21 );
  cages[8].push_back( 30 );
  // cage_9 = 8
  cages[9].push_back( 23 );
  cages[9].push_back( 32 );
  cages[9].push_back( 41 );
  // cage_10 = 20
  cages[10].push_back( 24 );
  cages[10].push_back( 25 );
  cages[10].push_back( 33 );
  // cage_11 = 6
  cages[11].push_back( 27 );
  cages[11].push_back( 36 );
  // cage_12 = 14
  cages[12].push_back( 28 );
  cages[12].push_back( 29 );
  // cage_13 = 17
  cages[13].push_back( 31 );
  cages[13].push_back( 40 );
  cages[13].push_back( 49 );
  // cage_14 = 17
  cages[14].push_back( 34 );
  cages[14].push_back( 42 );
  cages[14].push_back( 43 );
  // cage_15 = 13
  cages[15].push_back( 37 );
  cages[15].push_back( 38 );
  cages[15].push_back( 46 );
  // cage_16 = 20
  cages[16].push_back( 39 );
  cages[16].push_back( 48 );
  cages[16].push_back( 57 );
  // cage_17 = 12
  cages[17].push_back( 44 );
  cages[17].push_back( 53 );
  // cage_18 = 27
  cages[18].push_back( 45 );
  cages[18].push_back( 54 );
  cages[18].push_back( 63 );
  cages[18].push_back( 72 );
  // cage_19 = 6
  cages[19].push_back( 47 );
  cages[19].push_back( 55 );
  cages[19].push_back( 56 );
  // cage_20 = 20
  cages[20].push_back( 50 );
  cages[20].push_back( 59 );
  cages[20].push_back( 60 );
  // cage_21 = 6
  cages[21].push_back( 51 );
  cages[21].push_back( 52 );
  // cage_22 = 10
  cages[22].push_back( 58 );
  cages[22].push_back( 66 );
  cages[22].push_back( 67 );
  cages[22].push_back( 75 );
  // cage_23 = 14
  cages[23].push_back( 61 );
  cages[23].push_back( 62 );
  cages[23].push_back( 70 );
  cages[23].push_back( 71 );
  // cage_24 = 8
  cages[24].push_back( 64 );
  cages[24].push_back( 73 );
  // cage_25 = 16
  cages[25].push_back( 65 );
  cages[25].push_back( 74 );
  // cage_26 = 15
  cages[26].push_back( 68 );
  cages[26].push_back( 69 );
  // cage_27 = 13
  cages[27].push_back( 76 );
  cages[27].push_back( 77 );
  cages[27].push_back( 78 );
  // cage_28 = 17
  cages[28].push_back( 79 );
  cages[28].push_back( 80 );

  vector<int> rhs_eq{ 3, 15, 22, 4, 16, 15, 25, 17, 9, 8, 20, 6, 14, 17, 17, 13, 20, 12, 27, 6, 20, 6, 10, 14, 8, 16, 15, 13, 17 };

  //AllDiffConcept ad_concept_;
	unique_ptr<Concept> ad_concept_ = make_unique<AllDiffConcept>();
	vector< unique_ptr<Concept> > vec_le_concept_( 29 );
	for( int i = 0; i < 29; ++i )
		vec_le_concept_[i] = make_unique<LinearEqConcept>( rhs_eq[i] );
	
	int size_side = 9;
	int size_side_small_square = 3;

	std::vector<int> partial_sol( size_side );

	// Rows
	for( int i = 0; i < size_side; ++i )
	{
		std::copy( solution.begin() + ( i * size_side ),
		           solution.begin() + ( ( i + 1 ) * size_side ),
		           partial_sol.begin() );

		if( !ad_concept_->concept_( partial_sol ) )
		{
			std::cout << "Problem in row " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( std::cout, " " ) );
			std::cout << "\n";
		}
	}

	// Columns
	for( int i = 0; i < size_side; ++i )
	{
		for( int j = 0; j < size_side; ++j )
			partial_sol[j] = solution[ j * size_side + i ];

		if( !ad_concept_->concept_( partial_sol ) )
		{
			std::cout << "Problem in column " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( std::cout, " " ) );
			std::cout << "\n";
		}
	}

	// Squares
	for( int i = 0; i < size_side_small_square; ++i )
		for( int j = 0; j < size_side_small_square; ++j )
		{
			for( int k = 0; k < size_side_small_square; ++k )
				for( int l = 0; l < size_side_small_square; ++l )
				partial_sol[ k * size_side_small_square + l ] = solution[ i * ( size_side_small_square * size_side ) + j * size_side_small_square + k * size_side + l ];
			
			if( !ad_concept_->concept_( partial_sol ) )
			{
				std::cout << "Problem in square (" << i+1 << "," << j+1 << "): ";
				std::copy( partial_sol.begin(),
				           partial_sol.end(),
				           std::ostream_iterator<int>( std::cout, " " ) );
				std::cout << "\n";
			}
		}

	// Cages
	for( int i = 0; i < 29; ++i )
	{
		vector<int> partial_cage( cages[i].size() );
		for( int j = 0; j < (int)cages[i].size(); ++j )
			partial_cage[j] = solution[ cages[i][j] ];
			
		if( !vec_le_concept_[i]->concept_( partial_cage ) )
		{
			int sum = accumulate( partial_cage.begin(), partial_cage.end(), 0 );
			
			cout << "Problem in cage " << i << ": sum of ";
			std::copy( partial_cage.begin(),
			           partial_cage.end(),
			           std::ostream_iterator<int>( cout, " " ) );
			cout << "give " << sum << ", not " << rhs_eq[i] << "\n";
		}
	}
}
