#!/bin/bash

for i in {1..100}
do
		./bin/learn_cf_cp -c ad -i ../learn_ga/spaces/ad-12-12-10000-la.txt -n 12 -d 12 --xp --long >> results/ad-12-12-10000-la-30s.txt
		wait
		./bin/learn_cf_cp -c cm -i ../learn_ga/spaces/cm-12-12-10000-6-la.txt -n 12 -d 12 -p 6 --xp --long >> results/cm-12-12-10000-6-la-30s.txt
		wait
		./bin/learn_cf_cp -c le -i ../learn_ga/spaces/le-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/le-12-12-10000-42-la-30s.txt
		wait
		./bin/learn_cf_cp -c ll -i ../learn_ga/spaces/ll-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/ll-12-12-10000-42-la-30s.txt
		wait
		./bin/learn_cf_cp -c lg -i ../learn_ga/spaces/lg-12-12-10000-42-la.txt -n 12 -d 12 -p 42 --xp --long >> results/lg-12-12-10000-42-la-30s.txt
		wait
		./bin/learn_cf_cp -c lt -i ../learn_ga/spaces/lt-12-12-10000-la.txt -n 12 -d 12 --xp --long >> results/lt-12-12-10000-la-30s.txt
		wait
		./bin/learn_cf_cp -c ol -i ../learn_ga/spaces/ol-8-32-10000-3-la.txt -n 8 -d 32 -p 3 --xp --long >> results/ol-8-32-10000-3-la-30s.txt
done
