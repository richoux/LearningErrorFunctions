#!/bin/bash

g++ -O3 sol_repartition_estimator.cpp ../constraints/all-diff_concept.cpp ../constraints/less-than_concept.cpp ../constraints/linear-eq_concept.cpp ../constraints/connection-min-gt_concept.cpp ../constraints/overlap-1d_concept.cpp ../constraints/concept.cpp -I./include -o bin/sol_repartition_estimator
