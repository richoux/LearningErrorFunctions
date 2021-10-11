#!/bin/bash

g++ -std=c++20 -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp factory_sudoku.cpp ../../constraints/all-diff.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp ../../learn/function_to_learn_icn.cpp ../../utils/convert.cpp -o bin/sudoku -I../../learn/include -L../../learn/lib -lghost_static -pthread
