#!/bin/bash

g++ -O3 -DAD learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/all-diff_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I../explored/eo/include -L../explored/eo/lib -leo -leoutils -o bin/all_diff_cf_ga