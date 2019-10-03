#!/bin/bash

g++ -Ofast -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../constraints/all-diff.cpp ../cfn/function_to_learn_cppn.cpp -o bin/sudoku -lghost -pthread -DCPPN
