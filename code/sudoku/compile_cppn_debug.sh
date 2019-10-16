#!/bin/bash

g++ -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../constraints/all-diff.cpp ../cfn/function_to_learn_cppn.cpp ../constraints/concept.cpp -o bin/sudoku -lghost -pthread -DCPPN
