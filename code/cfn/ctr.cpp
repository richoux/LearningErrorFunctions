#include <algorithm>
#include <valarray>
#include <cmath>

#include "ctr.hpp"
#include "latin.hpp"
#include "function_to_learn.hpp"
#include "concept.hpp"

constexpr int ITER=10;

Ctr::Ctr( const vector< reference_wrapper<Variable> >& variables, const std::mt19937& gen )
	: Constraint (variables),
	  gen (gen),
	  rand_var (std::uniform_int_distribution<>{ 0, static_cast<int>( variables.size() ) - 1 }),
	  rand_val (std::uniform_int_distribution<>{ 0, static_cast<int>( variables[0].get().get_domain_size() ) - 1 })
{ }

double Ctr::required_cost() const
{
	auto samples = LHS( variables );
	
	double g_x, mean, std_dev, diff, max_diff;
	valarray<double> g_outputs( ITER );
	int max, index, value;

	max = variables[0].get().get_domain_size() - 1;
	max_diff = 0;
	
	for( const auto& s : samples )
	{
		if( !concept( s ) )
		{
			g_x = g( variables, s, max );

			for( int i = 0; i < ITER; ++i )
			{
				auto neighbor = s;
				
				do
				{
					index = rand_var( gen );
					value = rand_val( gen );
				}
				while( neighbor[ index ] == value );
				neighbor[ index ] = value;

				g_outputs[i] = g( variables, neighbor, max );				
			}

			mean = g_outputs.sum() / ITER;
			std_dev = 0.;
			for( const auto& g : g_outputs )
				std_dev += std::pow( ( g - mean ), 2 );
			std_dev /= ITER;
			std_dev = std::sqrt( std_dev );
			
			diff = std::abs( g_x - mean );
			if( diff > std_dev && diff > max_diff )
				max_diff = diff;
		}
	}
	
	return max_diff;
}

