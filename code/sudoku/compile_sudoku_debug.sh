#!/bin/bash

g++ -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../constraints/all-diff.cpp ../constraints/all-diff_concept.cpp ../constraints/concept.cpp ../learn/function_to_learn_cppn.cpp -o bin/sudoku -lghost -pthread
