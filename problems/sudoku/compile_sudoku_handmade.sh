#!/bin/bash

g++ -std=c++17 -DHANDMADE -DGHOST_BENCH -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter sudoku.cpp builder.cpp user_print.cpp ../../constraints/all-diff_handmade.cpp ../../constraints/all-diff_concept.cpp ../../constraints/concept.cpp -o bin/sudoku_handmade -I../../learn/include -L../../learn/lib -lghost_static -pthread
