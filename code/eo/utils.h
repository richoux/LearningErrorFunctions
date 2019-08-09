#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <iterator>
#include <algorithm>

struct ConfigCost
{
	std::vector<double> configuration;
	double cost;

	ConfigCost( const std::vector<double>& configuration, double cost )
		: configuration(configuration),
		  cost(cost)
	{ }
};

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
std::vector< ConfigCost > fetch_data( const std::string& filename )
{
	std::ifstream file( filename );
  auto dummy = get_next_line_and_split_into_tokens( file );
  
  std::vector< ConfigCost > data;
  
  while( file.good() )
  {
	  auto tokens = get_next_line_and_split_into_tokens( file );
	  std::vector<double> x;
	  double y = std::stod( tokens[2] );

	  std::transform( tokens.begin() + 3,
	                  tokens.end(),
	                  std::back_inserter( x ),
	                  [](auto i){ return std::stod( i ); } );
	  
	  data.emplace_back( x, y );
  }

  return data;
}

