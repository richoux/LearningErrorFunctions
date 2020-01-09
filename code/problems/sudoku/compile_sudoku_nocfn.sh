#!/bin/bash

g++ -DNOCFN -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../../constraints/all-diff_no-cfn.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_nocfn -lghost -pthread
