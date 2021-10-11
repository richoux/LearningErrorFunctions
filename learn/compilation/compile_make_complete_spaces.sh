#!/bin/bash

g++ -O3 make_complete_spaces.cpp ../constraints/all-diff_concept.cpp ../constraints/less-than_concept.cpp ../constraints/linear-eq_concept.cpp ../constraints/linear-leq_concept.cpp ../constraints/linear-geq_concept.cpp ../constraints/connection-min-gt_concept.cpp ../constraints/overlap-1d_concept.cpp ../constraints/concept.cpp ../utils/increment.cpp -I./include -o bin/make_complete_spaces
