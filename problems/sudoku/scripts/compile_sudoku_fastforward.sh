#!/bin/bash

g++ -std=c++17 -DFASTFORWARD -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/sudoku_fastforward ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/concept.cpp ../../../learn/function_to_learn_icn.cpp ../../../utils/convert.cpp -I../../../learn/include -I../src -L../../../learn/lib -lghost_static -pthread
