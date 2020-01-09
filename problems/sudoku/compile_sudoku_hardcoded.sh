#!/bin/bash

g++ -DHARDCODED -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../../constraints/all-diff_hardcoded.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_hardcoded -I../../learn/include -L../../learn/lib -lghost -pthread
