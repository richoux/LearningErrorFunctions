#!/bin/bash

g++ -O3 -DLT learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/less-than_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I./include -L./lib -leo -leoutils -o bin/less_than_cf_ga
