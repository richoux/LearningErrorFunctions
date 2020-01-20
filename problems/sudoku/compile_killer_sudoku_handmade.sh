#!/bin/bash

g++ -DHANDMADE -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter killer_sudoku.cpp ../../constraints/all-diff_handmade.cpp ../../constraints/all-diff_concept.cpp ../../constraints/linear-eq_handmade.cpp ../../constraints/linear-eq_concept.cpp ../../constraints/concept.cpp -o bin/killer_sudoku_handmade -I../../learn/include -L../../learn/lib -lghost -pthread
