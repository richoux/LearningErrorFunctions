/*
  Template for simple mutation operators
  ======================================
*/

#ifndef eoCFNMutation_H
#define eoCFNMutation_H


#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoCFNMutation: public eoMonOp<GenotypeT>
{
public:
	/**
	 * Ctor - no requirement
	 */
// START eventually add or modify the anyVariable argument
	eoCFNMutation(const double& _rate = 0.01, bool _normalize=false)
		rate(_rate), normalize(_normalize) {}

	/// The class name. Used to display statistics
	string className() const { return "eoCFNMutation"; }

	/**
	 * modifies the parent
	 * @param _genotype The parent genotype (will be modified)
	 */
	bool operator()(GenotypeT & _genotype)
	{
		double actualRate = (normalize ? rate/_genotype.size() : rate);
		bool changed_something = false;
		for (unsigned i = 0; i < _genotype.size(); i++)
			if (eo::rng.flip(actualRate))
			{
				_genotype[i] = !_genotype[i];
				changed_something = true;
			}
		
		return changed_something;
	}

private:
	double rate;
	bool normalize;
};

#endif
