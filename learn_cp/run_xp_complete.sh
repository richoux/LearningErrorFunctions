#!/bin/bash

for i in {1..100}
do
		./bin/learn_cf_cp -c ad -ci ../learn_ga/spaces/complete_ad-4-5.txt -n 4 -d 5 --xp >> results/complete_ad-4-5-200ms.txt
		wait
		./bin/learn_cf_cp -c cm -ci ../learn_ga/spaces/complete_cm-4-5-3.txt -n 4 -d 5 -p 3 --xp >> results/complete_cm-4-5-3-200ms.txt
		wait
		./bin/learn_cf_cp -c le -ci ../learn_ga/spaces/complete_le-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_le-3-8-12-200ms.txt
		wait
		./bin/learn_cf_cp -c ll -ci ../learn_ga/spaces/complete_ll-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_ll-3-8-12-200ms.txt
		wait
		./bin/learn_cf_cp -c lg -ci ../learn_ga/spaces/complete_lg-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_lg-3-8-12-200ms.txt
		wait
		./bin/learn_cf_cp -c lt -ci ../learn_ga/spaces/complete_lt-4-5.txt -n 4 -d 5 --xp >> results/complete_lt-4-5-200ms.txt
		wait
		./bin/learn_cf_cp -c ol -ci ../learn_ga/spaces/complete_ol-3-8-2.txt -n 3 -d 8 -p 2 --xp >> results/complete_ol-3-8-2-200ms.txt
done
