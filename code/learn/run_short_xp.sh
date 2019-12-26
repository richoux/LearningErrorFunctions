#!/bin/bash

for i in {1..100}; do
		./bin/learn_cf_ga -c le -n 3 -d 8 -p 12 -ci spaces/complete_le-3-8-12.txt --xp >> ./results/complete-le-3-8-12.txt
done
