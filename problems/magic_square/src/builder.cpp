#include "builder.hpp"

Builder::Builder( int instance_size )
	: ModelBuilder( true ),
	  _instance_size( instance_size ),
	  _nb_vars( _instance_size * _instance_size ),
	  _constant( _instance_size * ( _nb_vars - 1 ) / 2 ),
	  _rows( vector< vector<int> >( _instance_size ) ),
	  _columns( vector< vector<int> >( _instance_size ) ),
	  _diagonals( vector< vector<int> >( 2 ) )
{
	// Prepare row variables
  for( int row = 0; row < _instance_size; ++row )
	  for( int i = 0 ; i < _instance_size ; ++i )
		  _rows[row].push_back( i + ( row * _instance_size ) );
  
  // Prepare column variables
  for( int col = 0; col < _instance_size; ++col )
	  for( int row = 0; row < _instance_size; ++row )
		  _columns[ col ].push_back( col + ( row * _instance_size ) );
	  
  // Prepare diagonals variables
  for( int row = 0; row < _instance_size; ++row )
  {
	  _diagonals[ 0 ].push_back( row + ( row * _instance_size ) );
	  _diagonals[ 1 ].push_back( _instance_size - 1 - row + ( row * _instance_size ) );
  }
}

void Builder::declare_variables()
{
	create_n_variables( _nb_vars, 1, _nb_vars );

	for( int i = 0 ; i < _nb_vars ; ++i )
		variables[i].set_value( i + 1 );
}

void Builder::declare_constraints()
{
  for( int i = 0; i < _instance_size; ++i )
  {
	  constraints.emplace_back( make_shared< LinearEq >( _rows[i], _nb_vars, _constant ) );
	  constraints.emplace_back( make_shared< LinearEq >( _columns[i], _nb_vars, _constant ) );
  }

  constraints.emplace_back( make_shared< LinearEq >( _diagonals[0], _nb_vars, _constant ) );
  constraints.emplace_back( make_shared< LinearEq >( _diagonals[1], _nb_vars, _constant ) );
}
