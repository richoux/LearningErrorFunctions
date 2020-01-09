#include <string>

#include <eo>
#include <ga.h>

typedef eoBit<eoMinimizingFitness> Indi;

string transfo_operation( int number );
string compar_operation( int number );
void print_model( const Indi& indi );
void print_model( const string& indi );
void print_model( const vector<int>& indi );

