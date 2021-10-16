#!/bin/bash

# The correct (Manhattan fashion) Linear Leq handmand function is actually in constraints/linear-eq_hardcoded.cpp
# (what is in constraints/linear-eq_handmade.cpp is the Hamming handmade function)
g++ -std=c++17 -DHANDMADE -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/killer_sudoku_handmade ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff_handmade.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/linear-eq_hardcoded.cpp ../../../constraints/linear-eq_concept.cpp ../../../constraints/concept.cpp -I../../../learn/include -I../src -L../.xo./../learn/lib -lghost_static -pthread
