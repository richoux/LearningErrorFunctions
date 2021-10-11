#!/bin/bash

g++ -std=c++17 -DHANDMADE -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -o ../bin/sudoku_handmade ../../main.cpp ../src/builder.cpp ../src/user_print.cpp ../../../constraints/all-diff_handmade.cpp ../../../constraints/all-diff_concept.cpp ../../../constraints/concept.cpp -I../../../learn/include -I../src -L../.xo./../learn/lib -lghost_static -pthread
