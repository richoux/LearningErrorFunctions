#!/bin/bash

declare -a constraints=("le")
declare -a nb_vars=(6 9 12)

for c in ${constraints[@]}; do
    for n in ${nb_vars[@]}; do
				params=( $((2*$n)) $(($n*$n/2)) $(($n + $n*$n/2)) )
				for p in ${params[@]}; do
						for i in {1..100}; do
								./bin/learn_cf_ga -c $c -n $n -d $n -s 100 -p $p -l --xp >> ./results/$c-$n-$n-100-$p-la-gen.txt
						done
				done
    done
done
