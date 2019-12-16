#!/bin/bash

g++ -O0 -g -DDEBUG learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/all-diff_concept.cpp ../constraints/less-than_concept.cpp ../constraints/linear-eq_concept.cpp ../constraints/connection-min-gt_concept.cpp ../constraints/overlap-1d_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I./include -L./lib -leo -leoutils -o bin/learn_cf_ga_debug
