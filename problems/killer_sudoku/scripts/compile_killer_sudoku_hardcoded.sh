#!/bin/bash

g++ -std=c++17 -DHARDCODED -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/killer_sudoku_hardcoded ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff_hardcoded.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/linear-eq_hardcoded.cpp ../../../constraints/linear-eq_concept.cpp ../../../constraints/concept.cpp -I../../../learn/include -I../src -L../../../learn/lib -lghost_static -pthread
