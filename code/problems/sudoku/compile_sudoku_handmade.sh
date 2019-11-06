#!/bin/bash

g++ -DHANDMADE -Ofast -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../../constraints/all-diff_handmade.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_handmade -lghost -pthread
