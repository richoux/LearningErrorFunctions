#!/bin/bash


for i in {1..100}; do
    ./bin/learn_cf_ga -c ad -n 4 -d 5 -ci spaces/complete_ad-4-5.txt --xp >> ./results/complete/complete-ad-4-5_bis.txt &
    ./bin/learn_cf_ga -c cm -n 4 -d 5 -p 3 -ci spaces/complete_cm-4-5-3.txt --xp >> ./results/complete/complete-cm-4-5-3_bis.txt &
    ./bin/learn_cf_ga -c lt -n 4 -d 5 -ci spaces/complete_lt-4-5.txt --xp >> ./results/complete/complete-lt-4-5_bis.txt &
    ./bin/learn_cf_ga -c le -n 3 -d 8 -p 12 -ci spaces/complete_le-3-8-12.txt --xp >> ./results/complete/complete-le-3-8-12_bis.txt &
    ./bin/learn_cf_ga -c ol -n 3 -d 8 -p 2 -ci spaces/complete_ol-3-8-2.txt --xp >> ./results/complete/complete-ol-3-8-2_bis.txt &

		wait
done
