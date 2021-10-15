#include <memory>
#include <algorithm>
#include "../../constraints/linear-leq_concept.hpp"
#include "../../constraints/linear-geq_concept.hpp"

void check_solution( const vector<int>& solution )
{
	if( solution.size() != 20 )
		return;
	
	std::unique_ptr<Concept> le_concept = make_unique<LinearGeqConcept>( 3 );

	int a, b;

	a = 0;
	b = 1;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 0;
	b = 8;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 0;
	b = 9;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 1;
	b = 2;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 1;
	b = 8;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 2;
	b = 3;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 3;
	b = 7;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 3;
	b = 6;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 3;
	b = 5;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 3;
	b = 4;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 4;
	b = 6;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 4;
	b = 5;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 5;
	b = 6;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 5;
	b = 19;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 6;
	b = 16;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 6;
	b = 15;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 6;
	b = 7;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 7;
	b = 15;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 7;
	b = 8;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 8;
	b = 10;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 8;
	b = 9;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 9;
	b = 10;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 10;
	b = 11;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 10;
	b = 14;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 11;
	b = 12;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 12;
	b = 13;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 13;
	b = 14;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 14;
	b = 15;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 15;
	b = 16;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 16;
	b = 17;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";
	
	a = 17;
	b = 18;
	if( !le_concept->concept_( std::vector<int>{solution[a], solution[b]} ) )
		std::cout << "Problem for the edge (" << solution[a] << "," << solution[b] << ")\n";

	le_concept = make_unique<LinearLeqConcept>( 31 );
	if( !le_concept->concept_( solution ) )
	{
		auto selected = std::count_if( solution.begin(), solution.end(), [&](auto& s){return s == 2;} );
		std::cout << "Too many vertices selected: " << selected << "\n";
	}
}
