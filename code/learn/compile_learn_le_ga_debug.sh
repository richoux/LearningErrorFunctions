#!/bin/bash

g++ -O0 -DDEBUG -DLE learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/linear-eq_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I../explored/eo/include -L../explored/eo/lib -leo -leoutils -o bin/linear_eq_cf_ga
