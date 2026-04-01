#!/bin/bash

./bin/learn_cf_cp_complete_solver -c ad -i ../learn_ga/spaces/ad-12-12-10000-la.txt -n 12 -d 12 --xp --long > results/complete_search/ad-12-12-10000-la.txt
./bin/learn_cf_cp_complete_solver -c cm -i ../learn_ga/spaces/cm-12-12-10000-6-la.txt -n 12 -d 12 -p 6 --xp --long > results/complete_search/cm-12-12-10000-6-la.txt
./bin/learn_cf_cp_complete_solver -c le -i ../learn_ga/spaces/le-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long > results/complete_search/le-12-12-10000-42-la.txt
./bin/learn_cf_cp_complete_solver -c ll -i ../learn_ga/spaces/ll-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long > results/complete_search/ll-12-12-10000-42-la.txt
./bin/learn_cf_cp_complete_solver -c lg -i ../learn_ga/spaces/lg-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long > results/complete_search/lg-12-12-10000-42-la.txt
./bin/learn_cf_cp_complete_solver -c lt -i ../learn_ga/spaces/lt-12-12-10000-la.txt -n 12 -d 12 --xp --long > results/complete_search/lt-12-12-10000-la.txt
./bin/learn_cf_cp_complete_solver -c ol -i ../learn_ga/spaces/ol-8-32-10000-3-la.txt -n 8 -d 32 -p 3 --xp --long > results/complete_search/ol-8-32-10000-3-la.txt
