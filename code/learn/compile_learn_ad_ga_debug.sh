#!/bin/bash

g++ -g -O0 -DAD -DDEBUG learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/all-diff_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I./include -L./lib -leo -leoutils -o bin/all_diff_cf_ga
