#!/bin/bash

g++ -std=c++17 -DFASTFORWARD -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/killer_sudoku_fastforward ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/linear-eq.cpp ../../../constraints/linear-eq_concept.cpp ../../../constraints/concept.cpp ../../../learn_ga/function_to_learn_icn.cpp ../../../utils/convert.cpp -I../../../learn_ga/include -I../src -L../../../learn_ga/lib -lghost_static -pthread
