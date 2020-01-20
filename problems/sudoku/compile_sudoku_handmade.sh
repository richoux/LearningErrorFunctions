#!/bin/bash

g++ -DHANDMADE -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp ../../constraints/all-diff_handmade.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_handmade -I../../learn/include -L../../learn/lib -lghost -pthread
