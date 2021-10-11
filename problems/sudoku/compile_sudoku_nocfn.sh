#!/bin/bash

g++ -std=c++17 -DNOCFN -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp builder.cpp user_print.cpp ../../constraints/all-diff_no-cfn.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_nocfn -I../../learn/include -L../../learn/lib -lghost_static -pthread
