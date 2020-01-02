#!/bin/bash


for i in {1..100}; do
    # ./bin/learn_cf_ga -c ad -n 4 -d 4 -ci spaces/complete_ad-4-4.txt --xp >> ./results/new-complete/complete-ad-4-4.txt &
    # ./bin/learn_cf_ga -c ad -n 4 -d 5 -ci spaces/complete_ad-4-5.txt --xp >> ./results/new-complete/complete-ad-4-5.txt &
    # ./bin/learn_cf_ga -c cm -n 4 -d 5 -p 3 -ci spaces/complete_cm-4-5-3.txt --xp >> ./results/new-complete/complete-cm-4-5-3.txt &
    # ./bin/learn_cf_ga -c lt -n 4 -d 5 -ci spaces/complete_lt-4-5.txt --xp >> ./results/new-complete/complete-lt-4-5.txt &
    # ./bin/learn_cf_ga -c le -n 3 -d 8 -p 12 -ci spaces/complete_le-3-8-12.txt --xp >> ./results/new-complete/complete-le-3-8-12.txt &
    # ./bin/learn_cf_ga -c ol -n 3 -d 8 -p 2 -ci spaces/complete_ol-3-8-2.txt --xp >> ./results/new-complete/complete-ol-3-8-2.txt &

		# ./bin/learn_cf_ga -c cm -n 3 -d 11 -p 8 -ci spaces/complete_cm-3-11-8.txt --xp >> ./results/new-complete/complete-cm-3-11-8.txt &
    # ./bin/learn_cf_ga -c le -n 3 -d 11 -p 26 -ci spaces/complete_le-3-11-26.txt --xp >> ./results/new-complete/complete-le-3-11-26.txt &
    # ./bin/learn_cf_ga -c ol -n 3 -d 11 -p 3 -ci spaces/complete_ol-3-11-3.txt --xp >> ./results/new-complete/complete-ol-3-11-3.txt &

		./bin/learn_cf_ga -c cm -n 3 -d 11 -p 7 -ci spaces/complete_cm-3-11-7.txt --xp >> ./results/new-complete/complete-cm-3-11-7.txt &
		./bin/learn_cf_ga -c cm -n 3 -d 11 -p 6 -ci spaces/complete_cm-3-11-6.txt --xp >> ./results/new-complete/complete-cm-3-11-6.txt &
		./bin/learn_cf_ga -c cm -n 3 -d 11 -p 5 -ci spaces/complete_cm-3-11-5.txt --xp >> ./results/new-complete/complete-cm-3-11-5.txt &
		wait
done
