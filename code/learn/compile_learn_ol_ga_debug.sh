#!/bin/bash

g++ -O0 -g -DOL -DDEBUG learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/overlap-1d_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I../explored/eo/include -L../explored/eo/lib -leo -leoutils -o bin/overlap_1d_cf_ga
