#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdlib.h>
#include <utility>

std::vector<std::string> get_next_line_and_split_into_tokens( std::istream &str )
{
  std::vector<std::string> result;
  std::string line;
  std::getline(str, line);

  std::stringstream lineStream(line);
  std::string cell;

  while (std::getline(lineStream, cell, ',')) {
    result.push_back(cell);
  }
  // This checks for a trailing comma with no data after it.
  if (!lineStream && cell.empty()) {
    // If there was a trailing comma then add an empty element.
    result.push_back("");
  }
  return result;
}


// Get the cost for each configuration.
// Our goal is to learn a function outputting something close to these costs.
std::vector< std::pair<std::vector<double>, double>> fetch_data( const std::string& filename )
{
	std::ifstream file( filename );
  auto dummy = get_next_line_and_split_into_tokens( file );
  
  std::vector< std::pair<std::vector<double>, double>> data;
  
  while( file.good() )
  {
	  auto tokens = get_next_line_and_split_into_tokens( file );
	  std::vector<double> x;
	  double y = std::stod( tokens[2] );

	  for( auto it = tokens.begin() + 3; it < tokens.end(); ++it )
		  x.push_back( std::stod( *it ) );

	  data.push_back( std::make_pair( x, y ) );
  }

  return data;
}

