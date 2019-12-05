#!/bin/bash

g++ -O3 -DCM learn_cf_ga.cpp ./function_to_learn_cppn.cpp ../constraints/connection-min-gt_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp -I../explored/eo/include -L../explored/eo/lib -leo -leoutils -o bin/connec_min_gt_cf_ga
