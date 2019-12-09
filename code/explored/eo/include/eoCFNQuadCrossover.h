/*
Template for simple quadratic crossover operators
=================================================

Quadratic crossover operators modify the both genotypes
*/

#ifndef eoCFNQuadCrossover_H
#define eoCFNQuadCrossover_H

#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoCFNQuadCrossover: public eoQuadOp<GenotypeT>
{
public:
  /**
   * Ctor - no requirement
   */
// START eventually add or modify the anyVariable argument
  eoCFNQuadCrossover()
  //  eoCFNQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
// END eventually add or modify the anyVariable argument
  {
    // START Code of Ctor of an eoCFNEvalFunc object
    // END   Code of Ctor of an eoCFNEvalFunc object
  }

  /// The class name. Used to display statistics
  string className() const { return "eoCFNQuadCrossover"; }

  /**
   * eoQuad crossover - _genotype1 and _genotype2 are the (future)
   *       offspring, i.e. _copies_ of the parents, to be modified
   * @param _genotype1 The first parent
   * @param _genotype2 The second parent
   */
  bool operator()(GenotypeT& _genotype1, GenotypeT & _genotype2)
  {
	  unsigned site = eo::rng.random(std::min(_genotype1.size(), _genotype2.size()));
	  if (!std::equal(_genotype1.begin(), _genotype1.begin()+site, _genotype2.begin()))
	  {
		  std::swap_ranges(_genotype1.begin(), _genotype1.begin() + site, _genotype2.begin());
		  return true;
	  }
	  return false;
  }

private:
// START Private data of an eoCFNQuadCrossover object
  //  varType anyVariable;		   // for example ...
// END   Private data of an eoCFNQuadCrossover object
};

#endif
