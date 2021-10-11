#!/bin/bash

g++ -g -O0 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter ../main.cpp builder.cpp user_print.cpp ../../constraints/all-diff.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp ../../learn/function_to_learn_icn.cpp -o bin/sudoku_fastforward_debug -I../../learn/include -I. -L../../learn/lib -lghost -pthread
