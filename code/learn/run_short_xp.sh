#!/bin/bash


for i in {1..100}; do
		./bin/learn_cf_ga -c ad -n 4 -d 4 -ci spaces/complete_ad-4-4.txt --xp >> ./results/complete-ad-4-4_zeratul.txt &
		./bin/learn_cf_ga -c ad -n 4 -d 5 -ci spaces/complete_ad-4-5.txt --xp >> ./results/complete-ad-4-5_zeratul.txt &
		./bin/learn_cf_ga -c cm -n 4 -d 5 -p 3 -ci spaces/complete_cm-4-5-3.txt --xp >> ./results/complete-cm-4-5-3_zeratul.txt &
		./bin/learn_cf_ga -c lt -n 4 -d 5 -ci spaces/complete_lt-4-5.txt --xp >> ./results/complete-lt-4-5_zeratul.txt &
		./bin/learn_cf_ga -c ol -n 3 -d 7 -p 2 -ci spaces/complete_ol-3-7-2.txt --xp >> ./results/complete-ol-3-7-2_zeratul.txt &
		./bin/learn_cf_ga -c ol -n 3 -d 8 -p 2 -ci spaces/complete_ol-3-8-2.txt --xp >> ./results/complete-ol-3-8-2_zeratul.txt &
		./bin/learn_cf_ga -c ol -n 3 -d 8 -p 3 -ci spaces/complete_ol-3-8-3.txt --xp >> ./results/complete-ol-3-8-3_zeratul.txt &
		wait
done
