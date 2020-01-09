#!/bin/bash

declare -a constraints=("ol")
declare -a nb_vars=(6 9 12)

for c in ${constraints[@]}; do
    for n in ${nb_vars[@]}; do
				domains=( $((3*$n)) $((4*$n)) )
				for d in ${domains[@]}; do
						param=$(($d/$n - 1))
						for i in {1..100}; do
								./bin/learn_cf_ga -c $c -n $n -d $d -s 100 -p $param -l --xp >> ./results/$c-$n-$d-100-$param-la-gen.txt
						done
				done
    done
done
