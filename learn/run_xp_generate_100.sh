#!/bin/bash

declare -a constraints=("ad" "le" "lt" "ol" "cm" )
declare -a nb_vars=(6 9 12)

for c in ${constraints[@]}; do
    for n in ${nb_vars[@]}; do
	if [[ $c == "ad" ]] || [[ $c == "lt" ]]; then
	    for i in {1..100}; do
		./bin/learn_cf_ga -c $c -n $n -d $n -s 100 -l --xp >> ./results/$c-$n-$n-100-la-gen.txt
	    done
	    echo Subject: $c-$n-$n-100-la-gen finished > mail.txt
	    sendmail florian.richoux@polytechnique.edu < mail.txt
	fi
	if [[ $c == "lt" ]]; then
	    dom=$(($n + $n/2))
	    for i in {1..100}; do
		./bin/learn_cf_ga -c $c -n $n -d $dom -s 100 -l --xp >> ./results/$c-$n-$dom-100-la-gen.txt
	    done
	    echo Subject: $c-$n-$dom-100-la-gen finished > mail.txt
	    sendmail florian.richoux@polytechnique.edu < mail.txt
	fi
	if [[ $c == "le" ]]; then
	    params=( $((2*$n)) $(($n*$n/2)) $(($n + $n*$n/2)) )
	    for p in ${params[@]}; do
		for i in {1..100}; do
		    ./bin/learn_cf_ga -c $c -n $n -d $n -s 100 -p $p -l --xp >> ./results/$c-$n-$n-100-$p-la-gen.txt
		done
		echo Subject: $c-$n-$n-100-$p-la-gen finished > mail.txt
		sendmail florian.richoux@polytechnique.edu < mail.txt
	    done
	fi			
	if [[ $c == "cm" ]]; then
	    params=( $(($n/2)) $(($n/4)) $(($n/6)) )
	    for p in ${params[@]}; do
		for i in {1..100}; do
		    ./bin/learn_cf_ga -c $c -n $n -d $n -s 100 -p $p -l --xp >> ./results/$c-$n-$n-100-$p-la-gen.txt
		done
		echo Subject: $c-$n-$n-100-$p-la-gen finished > mail.txt
		sendmail florian.richoux@polytechnique.edu < mail.txt
	    done
	fi			
	if [[ $c == "ol" ]]; then
	    domains=( $((3*$n)) $((4*$n)) )
	    for d in ${domains[@]}; do
		param=$(($d/$n - 1))
		for i in {1..100}; do
		    ./bin/learn_cf_ga -c $c -n $n -d $d -s 100 -p $param -l --xp >> ./results/$c-$n-$d-100-$param-la-gen.txt
		done
		echo Subject: $c-$n-$d-100-$param-la-gen finished > mail.txt
		sendmail florian.richoux@polytechnique.edu < mail.txt
	    done
	fi			
    done
done
