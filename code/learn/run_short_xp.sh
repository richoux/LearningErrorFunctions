#!/bin/bash

for i in {1..100}; do
		./bin/learn_cf_ga -c ol -n 3 -d 8 -p 2 -ci spaces/complete_ol-3-8-2.txt --xp >> ./results/complete-ol-3-8-2.txt
done
