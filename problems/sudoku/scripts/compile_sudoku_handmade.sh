#!/bin/bash

g++ -std=c++17 -DHANDMADE -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/sudoku_handmade ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff_handmade.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/concept.cpp -I../../../learn_ga/include -I../src -L../../../learn_ga/lib -lghost_static -pthread
