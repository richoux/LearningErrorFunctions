#!/bin/bash

g++ -O3 get_score.cpp ./function_to_learn_icn.cpp ../constraints/all-diff_concept.cpp ../constraints/less-than_concept.cpp ../constraints/linear-eq_concept.cpp ../constraints/connection-min-gt_concept.cpp ../constraints/overlap-1d_concept.cpp ../constraints/concept.cpp ../utils/metrics.cpp ../utils/random_draw.cpp ../utils/convert.cpp ../utils/latin.cpp ../utils/print.cpp -Iinclude -o bin/get_score
