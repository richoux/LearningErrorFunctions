#pragma once

#include <vector>
#include <memory>

#include "subghost/variable.hpp"
#include "subghost/constraint.hpp"

using namespace std;
using namespace ghost;

double hamming( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables );

double manhattan( const shared_ptr<Constraint> constraint,
                  const vector< reference_wrapper<Variable> >& variables );

double ham_man( const shared_ptr<Constraint> constraint,
                const vector< reference_wrapper<Variable> >& variables );
