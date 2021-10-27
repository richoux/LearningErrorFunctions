#include <memory>
#include <algorithm>
#include "../../constraints/linear-eq_concept.hpp"

void check_solution( const vector<int>& solution )
{
	int nb_vars = static_cast<int>( solution.size() );
	int order = static_cast<int>( std::sqrt( nb_vars ) );
	int constant = order * ( nb_vars + 1 ) / 2;

	std::unique_ptr<Concept> le_concept = make_unique<LinearEqConcept>( constant );
	
	std::vector<int> partial_sol( order );

	// Rows
	for( int i = 0; i < order; ++i )
	{
		std::copy( solution.begin() + ( i * order ),
		           solution.begin() + ( ( i + 1 ) * order ),
		           partial_sol.begin() );

		if( !le_concept->concept_( partial_sol ) )
		{
			int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
			
			std::cout << "Problem in row " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( std::cout, " " ) );
			std::cout << "=> the sum is " << sum << " rather than " << constant << "\n";
		}
	}

	// Columns
	for( int i = 0; i < order; ++i )
	{
		for( int j = 0; j < order; ++j )
			partial_sol[j] = solution[ j * order + i ];

		if( !le_concept->concept_( partial_sol ) )
		{
			int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );

			std::cout << "Problem in column " << i+1 << ": ";
			std::copy( partial_sol.begin(),
			           partial_sol.end(),
			           std::ostream_iterator<int>( std::cout, " " ) );
			std::cout << "=> the sum is " << sum << " rather than " << constant << "\n";
		}
	}

	// Diagonal 0
	for( int i = 0; i < order; ++i )
		partial_sol[i] = solution[ i + ( i * order ) ];
		                           
	if( !le_concept->concept_( partial_sol ) )
	{
		int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
		
		std::cout << "Problem in diagonal 0: ";
		std::copy( partial_sol.begin(),
		           partial_sol.end(),
		           std::ostream_iterator<int>( std::cout, " " ) );
		std::cout << "=> the sum is " << sum << " rather than " << constant << "\n";
	}

	// Diagonal 1
	for( int i = 0; i < order; ++i )
		partial_sol[i] = solution[ order - 1 - i + ( i * order ) ];
		                           
	if( !le_concept->concept_( partial_sol ) )
	{
		int sum = std::accumulate( partial_sol.begin(), partial_sol.end(), 0 );
		
		std::cout << "Problem in diagonal 1: ";
		std::copy( partial_sol.begin(),
		           partial_sol.end(),
		           std::ostream_iterator<int>( std::cout, " " ) );
		std::cout << "=> the sum is " << sum << " rather than " << constant << "\n";
	}
}
