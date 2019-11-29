#pragma once

#include <string>
#include <vector>

std::string convert( const std::vector<int>& vec );
std::string convert( const std::vector<int>& vec, int start, int end );
std::vector<int> make_weights( const std::vector<int>& raw_weights );
std::vector<int> recover_raw_weights( const std::vector<int>& weights );
