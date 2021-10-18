#!/bin/bash

for i in {1..100}
do
		/bin/learn_cf_cp -c ad -ci ../learn_ga/spaces/complete_ad-4-5.txt -n 4 -d 5 --xp >> results/complete_ad-4-5.txt
		wait
		/bin/learn_cf_cp -c cm -ci ../learn_ga/spaces/complete_cm-4-5-3.txt -n 4 -d 5 -p 3 --xp >> results/complete_cm-4-5-3.txt
		wait
		/bin/learn_cf_cp -c le -ci ../learn_ga/spaces/complete_le-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_le-3-8-12.txt
		wait
		/bin/learn_cf_cp -c ll -ci ../learn_ga/spaces/complete_ll-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_ll-3-8-12.txt
		wait
		/bin/learn_cf_cp -c lg -ci ../learn_ga/spaces/complete_lg-3-8-12.txt -n 3 -d 8 -p 12 --xp >> results/complete_lg-3-8-12.txt
		wait
		/bin/learn_cf_cp -c lt -ci ../learn_ga/spaces/complete_lt-4-5.txt -n 4 -d 5 --xp >> results/complete_lt-4-5.txt
		wait
		/bin/learn_cf_cp -c ol -ci ../learn_ga/spaces/complete_ol-3-8-2.txt -n 3 -d 8 -p 2 --xp >> results/complete_ol-3-8-2.txt
		wait
		/bin/learn_cf_cp -c ad -i ../learn_ga/spaces/ad-12-12-10000-la.txt -n 12 -d 12 --xp --long >> results/ad-12-12-10000-la.txt
		wait
		/bin/learn_cf_cp -c cm -i ../learn_ga/spaces/cm-12-12-10000-6-la.txt -n 12 -d 12 -p 6 --xp --long >> results/cm-12-12-10000-6-la.txt
		wait
		/bin/learn_cf_cp -c le -i ../learn_ga/spaces/le-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/le-12-12-10000-42-la.txt
		wait
		/bin/learn_cf_cp -c ll -i ../learn_ga/spaces/ll-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/ll-12-12-10000-42-la.txt
		wait
		/bin/learn_cf_cp -c lg -i ../learn_ga/spaces/lg-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/lg-12-12-10000-42-la.txt
		wait
		/bin/learn_cf_cp -c lt -i ../learn_ga/spaces/lt-12-12-10000-la.txt -n 12 -d 12 --xp --long >> results/lt-12-12-10000-la.txt
		wait
		/bin/learn_cf_cp -c ol -i ../learn_ga/spaces/ol-8-32-10000-3-la.txt -n 8 -d 32 -p 3 --xp --long >> results/ol-8-32-10000-3-la.txt
done
