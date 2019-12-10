#!/bin/bash

g++ -O3 -DLE learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/linear-eq_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I./include -L./lib -leo -leoutils -o bin/linear_eq_cf_ga
