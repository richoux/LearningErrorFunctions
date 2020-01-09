/*
  Template for simple mutation operators
  ======================================
*/

#ifndef eoCFNMutation_H
#define eoCFNMutation_H

#include <algorithm>
#include <string>

#if defined DEBUG
#include <iostream>
#include <iterator>
#endif

#include <eoOp.h>

using namespace std;

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoCFNMutation : public eoMonOp<GenotypeT>
{
	int _number_units_transfo;
	int _number_units_compar;
	double _rate;
	bool _normalize;

public:
	/**
	 * Ctor - no requirement
	 */
	eoCFNMutation( int number_units_transfo, int number_units_compar )
		: _number_units_transfo( number_units_transfo ),
		  _number_units_compar( number_units_compar )
	{}

	/// The class name. Used to display statistics
	string className() const { return "eoCFNMutation"; }

	/**
	 * modifies the parent
	 * @param genotype The parent genotype (will be modified)
	 */
	bool operator()( GenotypeT& genotype )
	{
		bool changed_something = false;
		auto active_transfo_units = std::count( genotype.begin(), genotype.begin() + _number_units_transfo, true );
		auto active_compar_units = std::count( std::prev( genotype.end(), _number_units_compar ), genotype.end(), true );

#if defined DEBUG
		cout << "Before flipping: ";
		std::copy( genotype.begin(), genotype.end(), std::ostream_iterator<int>( cout, " " ) );
		cout << "\n";
#endif
	
		unsigned i;

		// Mutate one bit only
		// Forbid flipping the unique active unit in the transformation layer. 

		do
		{
			i = eo::rng.random( genotype.size() );
		} while( i < _number_units_transfo && active_transfo_units == 1 && genotype[i] );
		
		// If we are about to flip a comparison unit, switch all of them to false to have a unique active unit in this layer.
		if( i >= (int)genotype.size() - _number_units_compar )
			std::fill( std::prev( genotype.end(), _number_units_compar ), genotype.end(), false );
		genotype[i] = !genotype[i];
		changed_something = true;
		
#if defined DEBUG
		if( changed_something )
		{
			cout << "After flipping:  ";
			std::copy( genotype.begin(), genotype.end(), std::ostream_iterator<int>( cout, " " ) );
			cout << "\n";
		}
#endif
		
		return changed_something;
	}
};

#endif
