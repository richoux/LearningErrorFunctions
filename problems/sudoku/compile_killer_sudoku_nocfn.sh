#!/bin/bash

g++ -DNOCFN -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter killer_sudoku.cpp ../../constraints/all-diff_no-cfn.cpp ../../constraints/all-diff_concept.cpp ../../constraints/linear-eq_no-cfn.cpp ../../constraints/linear-eq_concept.cpp ../../constraints/concept.cpp -o bin/killer_sudoku_nocfn -I../../learn/include -L../../learn/lib -lghost -pthread
