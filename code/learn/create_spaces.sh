#!/bin/bash

declare -a constraints=("ad" "lt")
#declare -a constraints=("ad" "le" "lt" "ol" "cm" )
declare -a nb_vars=(2 3 4)

for c in ${constraints[@]}; do
		for n in ${nb_vars[@]}; do
				./bin/make_spaces -c $c -n $n -d $n -l -s 100 -o spaces/$c-$n-$n-100-la.txt > spaces/$c-$n-$n-100-la_data.txt
		done
done
