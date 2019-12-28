#!/bin/bash

for i in {1..100}; do
		./bin/learn_cf_ga -c ad -n 4 -d 5 -ci spaces/complete_ad-4-5.txt --xp >> ./results/complete-ad-4-5.txt
done
