#!/bin/bash

sum=0
declare -a costs
declare -A solutions

while IFS= read -r line
do
		words=($line)
		sum=$(echo "$sum + ${words[0]}" | bc)
		costs+=(${words[0]})

		beginning_sol=$(echo ${words[2]} | cut -c1-18)
		nb_ones=$(awk -F"1" '{print NF-1}' <<< "${beginning_sol}")
		if [ $nb_ones == 1 ]; then
				to_consider="${words[2]:0:18}0${words[2]:19}"
		else
				to_consider=${words[2]}
		fi

		# echo "original:    ${words[2]}"
		# echo "transformed: $to_consider"
		
		if [ ${solutions[$to_consider]} ]; then
				solutions[$to_consider]=$((${solutions[$to_consider]}+1))
		else
				solutions[$to_consider]=1
		fi
done < "$1"

sorted_solutions=$(for k in "${!solutions[@]}"
do
    echo $k ${solutions[$k]}
done |
sort -rn -k2)

echo "${sorted_solutions[@]}"

med=$(echo ${costs[@]} | sort | awk -f median.awk)
echo "Median: $med"

cost=$(echo "scale=3; $sum/100" | bc)
echo "Mean: $cost"
