#!/bin/bash

g++ -DNOCFN -O3 -W -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter magic_square.cpp ../../constraints/linear-eq_no-cfn.cpp ../../constraints/linear-eq_concept.cpp ../../constraints/concept.cpp -o bin/magic_square_nocfn -I../../learn/include -L../../learn/lib -lghost -pthread
