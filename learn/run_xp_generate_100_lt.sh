#!/bin/bash

declare -a constraints=("lt")
declare -a nb_vars=(6 9 12)

for c in ${constraints[@]}; do
    for n in ${nb_vars[@]}; do
				for i in {1..100}; do
						./bin/learn_cf_ga -c $c -n $n -d $n -s 100 -l --xp >> ./results/$c-$n-$n-100-la-gen.txt
				done

				dom=$(($n + $n/2))
				for i in {1..100}; do
						./bin/learn_cf_ga -c $c -n $n -d $dom -s 100 -l --xp >> ./results/$c-$n-$dom-100-la-gen.txt
				done
    done
done
