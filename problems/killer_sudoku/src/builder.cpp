#include "builder.hpp"

Builder::Builder( int instance_size )
	: ModelBuilder( true ),
	  _instance_size( 3 ),
	  _side_size( 9 ),
	  _nb_vars( 81 ),
	  _rows( vector< vector<int> >( 9 ) ),
	  _columns( vector< vector<int> >( 9 ) ),
	  _squares( vector< vector<int> >( 9 ) ),
	  _cages( vector< vector<int> >( 29 ) )
{ }

void Builder::declare_variables()
{
	create_n_variables( _nb_vars, 1, _side_size );

	for( int i = 0 ; i < _nb_vars ; ++i )
		variables[i].set_value( ( i % _side_size ) + 1 );
}

void Builder::declare_constraints()
{
  // Prepare row variables
  for( int r = 0; r < _side_size; ++r )
  {
	  _rows[r].clear();
	  for( int e = r * _side_size ; e < ( r + 1 ) * _side_size ; ++e )
		  _rows[r].push_back( e );
  }
  
  // Prepare column variables
  for( int c = 0; c < _side_size; ++c )
  {
	  _columns[c].clear();
	  for( int e = 0; e < _side_size; ++e )
		  _columns[c].push_back( c + ( e * _side_size ) );
  }
  
  // Prepare square variables
  for( int s_r = 0; s_r < _instance_size; ++s_r )
	  for( int s_c = 0; s_c < _instance_size; ++s_c )
	  {
		  _squares[ ( s_r * _instance_size ) + s_c ].clear();
		  for( int c = 0; c < _instance_size; ++c )
			  for( int r = 0; r < _instance_size; ++r )
			  {
				  _squares[ ( s_r * _instance_size ) + s_c ].push_back( r + ( s_r * _side_size * _instance_size )
				                                                        + ( s_c * _instance_size )
				                                                        + ( c * _side_size ) );
			  }
	  }

  // Prepare _cages variables: problem instance from http://www.csplib.org/Problems/prob057/
  // cage_0 = 3
  _cages[0].push_back( 0 );
  _cages[0].push_back( 1 );
  // cage_1 = 15
  _cages[1].push_back( 2 );
  _cages[1].push_back( 3 );
  _cages[1].push_back( 4 );
  // cage_2 = 22
  _cages[2].push_back( 5 );
  _cages[2].push_back( 13 );
  _cages[2].push_back( 14 );
  _cages[2].push_back( 22 );
  // cage_3 = 4
  _cages[3].push_back( 6 );
  _cages[3].push_back( 15 );
  // cage_4 = 16
  _cages[4].push_back( 7 );
  _cages[4].push_back( 16 );
  // cage_5 = 15
  _cages[5].push_back( 8 );
  _cages[5].push_back( 17 );
  _cages[5].push_back( 26 );
  _cages[5].push_back( 35 );
  // cage_6 = 25
  _cages[6].push_back( 9 );
  _cages[6].push_back( 10 );
  _cages[6].push_back( 18 );
  _cages[6].push_back( 19 );
  // cage_7 = 17
  _cages[7].push_back( 11 );
  _cages[7].push_back( 12 );
  // cage_8 = 9
  _cages[8].push_back( 20 );
  _cages[8].push_back( 21 );
  _cages[8].push_back( 30 );
  // cage_9 = 8
  _cages[9].push_back( 23 );
  _cages[9].push_back( 32 );
  _cages[9].push_back( 41 );
  // cage_10 = 20
  _cages[10].push_back( 24 );
  _cages[10].push_back( 25 );
  _cages[10].push_back( 33 );
  // cage_11 = 6
  _cages[11].push_back( 27 );
  _cages[11].push_back( 36 );
  // cage_12 = 14
  _cages[12].push_back( 28 );
  _cages[12].push_back( 29 );
  // cage_13 = 17
  _cages[13].push_back( 31 );
  _cages[13].push_back( 40 );
  _cages[13].push_back( 49 );
  // cage_14 = 17
  _cages[14].push_back( 34 );
  _cages[14].push_back( 42 );
  _cages[14].push_back( 43 );
  // cage_15 = 13
  _cages[15].push_back( 37 );
  _cages[15].push_back( 38 );
  _cages[15].push_back( 46 );
  // cage_16 = 20
  _cages[16].push_back( 39 );
  _cages[16].push_back( 48 );
  _cages[16].push_back( 57 );
  // cage_17 = 12
  _cages[17].push_back( 44 );
  _cages[17].push_back( 53 );
  // cage_18 = 27
  _cages[18].push_back( 45 );
  _cages[18].push_back( 54 );
  _cages[18].push_back( 63 );
  _cages[18].push_back( 72 );
  // cage_19 = 6
  _cages[19].push_back( 47 );
  _cages[19].push_back( 55 );
  _cages[19].push_back( 56 );
  // cage_20 = 20
  _cages[20].push_back( 50 );
  _cages[20].push_back( 59 );
  _cages[20].push_back( 60 );
  // cage_21 = 6
  _cages[21].push_back( 51 );
  _cages[21].push_back( 52 );
  // cage_22 = 10
  _cages[22].push_back( 58 );
  _cages[22].push_back( 66 );
  _cages[22].push_back( 67 );
  _cages[22].push_back( 75 );
  // cage_23 = 14
  _cages[23].push_back( 61 );
  _cages[23].push_back( 62 );
  _cages[23].push_back( 70 );
  _cages[23].push_back( 71 );
  // cage_24 = 8
  _cages[24].push_back( 64 );
  _cages[24].push_back( 73 );
  // cage_25 = 16
  _cages[25].push_back( 65 );
  _cages[25].push_back( 74 );
  // cage_26 = 15
  _cages[26].push_back( 68 );
  _cages[26].push_back( 69 );
  // cage_27 = 13
  _cages[27].push_back( 76 );
  _cages[27].push_back( 77 );
  _cages[27].push_back( 78 );
  // cage_28 = 17
  _cages[28].push_back( 79 );
  _cages[28].push_back( 80 );
  
  for( int i = 0; i < _side_size; ++i )
  {
	  constraints.emplace_back( make_shared<AllDiff>( _rows[i] ) );
	  constraints.emplace_back( make_shared<AllDiff>( _columns[i] ) );
	  constraints.emplace_back( make_shared<AllDiff>( _squares[i] ) );
  }

  vector<int> rhs_eq{ 3, 15, 22, 4, 16, 15, 25, 17, 9, 8, 20, 6, 14, 17, 17, 13, 20, 12, 27, 6, 20, 6, 10, 14, 8, 16, 15, 13, 17 };
  for( int i = 0; i < 29; ++i )
	  constraints.emplace_back( make_shared<LinearEq>( _cages[i], _side_size, rhs_eq[i] ) );
}
