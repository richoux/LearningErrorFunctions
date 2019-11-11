#!/bin/bash

g++ -std=c++17 -o bin/tests_if_scale tests_if_scale.cpp ../utils/metrics.cpp ../utils/convert.cpp ../constraints/concept.cpp ../constraints/all-diff.cpp ../constraints/all-diff_concept.cpp ../utils/random_draw.cpp ../learn/function_to_learn_cppn.cpp ../utils/latin.cpp -DAD -lghost
