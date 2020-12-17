#!/bin/bash


for i in {1..10}; do
    ./bin/learn_cf_ga -c ad -n 5 -d 5 -ci spaces/complete_ad-5-5.txt --xp --mingen 400 >> ./results/complete/complete-ad-5-5.txt &
    ./bin/learn_cf_ga -c cm -n 3 -d 11 -p 8 -ci spaces/complete_cm-3-11-8.txt --xp --mingen 400 >> ./results/complete/complete-cm-3-11-8.txt &
    ./bin/learn_cf_ga -c lt -n 5 -d 5 -ci spaces/complete_lt-5-5.txt --xp --mingen 400 >> ./results/complete/complete-lt-5-5.txt &
    ./bin/learn_cf_ga -c le -n 3 -d 11 -p 23 -ci spaces/complete_le-3-11-23.txt --xp --mingen 400 >> ./results/complete/complete-le-3-11-23.txt &
    ./bin/learn_cf_ga -c ol -n 3 -d 8 -p 3 -ci spaces/complete_ol-3-8-3.txt --xp --mingen 400 >> ./results/complete/complete-ol-3-8-3.txt &

		wait
done
