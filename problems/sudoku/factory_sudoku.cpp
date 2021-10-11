#include "factory_sudoku.hpp"

FactorySudoku::FactorySudoku( const std::vector<Variable>& variables, 
                              int instance_size )
	: FactoryModel( variables ),
	  _instance_size( instance_size ),
	  _side_size( instance_size * instance_size ),
	  _rows( vector< vector<int> >( _side_size ) ),
	  _columns( vector< vector<int> >( _side_size ) ),
	  _squares( vector< vector<int> >( _side_size ) )
{ }

void FactorySudoku::declare_constraints()
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
	
  for( int i = 0; i < _side_size; ++i )
  {
	  constraints.emplace_back( make_shared<AllDiff>( _rows[i] ) );
	  constraints.emplace_back( make_shared<AllDiff>( _columns[i] ) );
	  constraints.emplace_back( make_shared<AllDiff>( _squares[i] ) );
  }
}
