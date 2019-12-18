#!/bin/bash

#declare -a constraints=("ad" "lt")
declare -a constraints=("ad" "le" "lt" "ol" "cm" )
declare -a nb_vars=(6 9 12 15)
declare -a samplings=(100 1000 10000 100000)

for c in ${constraints[@]}; do
		for n in ${nb_vars[@]}; do
				for s in ${samplings[@]}; do
						if [[ $c == "ad" ]] || [[ $c == "lt" ]]; then
								./bin/make_spaces -c $c -n $n -d $n -s $s -l -o spaces/$c-$n-$n-$s-la.txt > spaces/$c-$n-$n-$s-la_data.txt
								if [[ $s == 100 ]]; then
										./bin/sol_repartition_estimator -c $c -n $n -d $n -s 1000000000 > spaces/repart-$c-$n-$n-1B.txt
								fi
						fi
						if [[ $c == "lt" ]]; then
								dom=$(($n + $n/2))
								./bin/make_spaces -c $c -n $n -d $dom -s $s -l -o spaces/$c-$n-$dom-$s-la.txt > spaces/$c-$n-$dom-$s-la_data.txt
								if [[ $s == 100 ]]; then
										./bin/sol_repartition_estimator -c $c -n $n -d $dom -s 1000000000 > spaces/repart-$c-$n-$dom-1B.txt
								fi
						fi
						if [[ $c == "le" ]]; then
								params=( $((2*$n)) $(($n*$n/2)) $(($n + $n*$n/2)) )
								for p in ${params[@]}; do
										./bin/make_spaces -c $c -n $n -d $n -s $s -p $p -l -o spaces/$c-$n-$n-$s-$p-la.txt > spaces/$c-$n-$n-$s-$p-la_data.txt
								if [[ $s == 100 ]]; then
										./bin/sol_repartition_estimator -c $c -n $n -d $n -s 1000000000 -p $p > spaces/repart-$c-$n-$n-1B-$p.txt
								fi
								done
						fi			
						if [[ $c == "cm" ]]; then
								params=( $(($n/2)) $(($n/4)) $(($n/6)) )
								for p in ${params[@]}; do
										./bin/make_spaces -c $c -n $n -d $n -s $s -p $p -l -o spaces/$c-$n-$n-$s-$p-la.txt > spaces/$c-$n-$n-$s-$p-la_data.txt
								if [[ $s == 100 ]]; then
										./bin/sol_repartition_estimator -c $c -n $n -d $n -s 1000000000 -p $p > spaces/repart-$c-$n-$n-1B-$p.txt
								fi
								done
						fi			
						if [[ $c == "ol" ]]; then
								domains=( $((3*$n)) $((4*$n)) )
								for d in ${domains[@]}; do
										param=$(($d/$n - 1))
										./bin/make_spaces -c $c -n $n -d $d -s $s -p $param -l -o spaces/$c-$n-$d-$s-$param-la.txt > spaces/$c-$n-$d-$s-$param-la_data.txt
								if [[ $s == 100 ]]; then
										./bin/sol_repartition_estimator -c $c -n $n -d $d -s 1000000000 -p $param > spaces/repart-$c-$n-$d-1B-$param.txt
								fi
								done
						fi			
				done
		done
done
