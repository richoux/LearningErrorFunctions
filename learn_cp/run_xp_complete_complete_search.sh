#!/bin/bash

./bin/learn_cf_cp_complete_solver -c ad -ci ../learn_ga/spaces/complete_ad-4-5.txt -n 4 -d 5 --xp > results/complete_search/complete_ad-4-5.txt
./bin/learn_cf_cp_complete_solver -c cm -ci ../learn_ga/spaces/complete_cm-4-5-3.txt -n 4 -d 5 -p 3 --xp > results/complete_search/complete_cm-4-5-3.txt
./bin/learn_cf_cp_complete_solver -c le -ci ../learn_ga/spaces/complete_le-3-8-12.txt -n 3 -d 8 -p 12 --xp > results/complete_search/complete_le-3-8-12.txt
./bin/learn_cf_cp_complete_solver -c ll -ci ../learn_ga/spaces/complete_ll-3-8-12.txt -n 3 -d 8 -p 12 --xp > results/complete_search/complete_ll-3-8-12.txt
./bin/learn_cf_cp_complete_solver -c lg -ci ../learn_ga/spaces/complete_lg-3-8-12.txt -n 3 -d 8 -p 12 --xp > results/complete_search/complete_lg-3-8-12.txt
./bin/learn_cf_cp_complete_solver -c lt -ci ../learn_ga/spaces/complete_lt-4-5.txt -n 4 -d 5 --xp > results/complete_search/complete_lt-4-5.txt
./bin/learn_cf_cp_complete_solver -c ol -ci ../learn_ga/spaces/complete_ol-3-8-2.txt -n 3 -d 8 -p 2 --xp > results/complete_search/complete_ol-3-8-2.txt
