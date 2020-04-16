#!/bin/bash

g++ -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter magic_square.cpp ../../constraints/linear-eq.cpp ../../constraints/linear-eq_concept.cpp ../../constraints/concept.cpp ../../learn/function_to_learn_icn.cpp -o bin/magic_square -I../../learn/include -L../../learn/lib -lghost -pthread
