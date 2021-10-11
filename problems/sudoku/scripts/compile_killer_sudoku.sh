#!/bin/bash

g++ -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter killer_sudoku.cpp ../../constraints/all-diff.cpp ../../constraints/all-diff_concept.cpp ../../constraints/linear-eq.cpp ../../constraints/linear-eq_concept.cpp ../../constraints/concept.cpp ../../learn/function_to_learn_icn.cpp -o bin/killer_sudoku -I../../learn/include -L../../learn/lib -lghost -pthread
