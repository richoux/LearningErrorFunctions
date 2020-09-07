#!/bin/bash

sum=0
declare -A solutions

while IFS= read -r line
do
		words=($line)
		sum=$(echo "$sum + ${words[0]}" | bc)
		echo "${words[0]}" >> costfile

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

filename=${1%.*}

IFS=- read var1 var2 var3 var4 var5 <<< $filename

if [[ $var1 == *"complete"* ]]; then
		nb_var=${var3}
		domain_size=${var4}
		space_size=$((domain_size ** nb_var))
else
		space_size=200
fi
echo "space_size = $space_size"

med=$(sort -g costfile | awk -f median.awk)
med_int=${med%.*}
# med_int=$(($med_int / $space_size))
med_int=$(bc <<<"scale=3;$med_int/$space_size")

echo "Median: $med_int"

# plop=$(cat costfile)
# echo $plop | tr " " ", "

cost=$(echo "scale=3; $sum/100" | bc)
cost_int=${cost%.*}
cost_int=$(bc <<<"scale=3;$cost_int/$space_size")
std_dev=$(cat costfile | awk -F' ' '{sum+=$1; sumsq+=$1*$1} END {print sqrt(($med*$med*NR - $med*sum + sumsq)/(NR-1))}')
std_dev=$(bc <<<"scale=3;$std_dev/$space_size")
echo "Mean: $cost_int"
echo "Sample standard deviation: $std_dev"
rm -f costfile

split=(${sorted_solutions[@]})
echo 
echo "//////////"
echo "Model of the most commun cost function ${split[0]}:"
echo 
./bin/print_model "${split[0]}"

if [[ ${split[2]} ]]; then
		echo 
		echo "//////////"
		echo "Model of the second most commun cost function ${split[2]}:"
		echo 
		./bin/print_model "${split[2]}"
fi

if [[ ${split[4]} ]]; then
		echo 
		echo "//////////"
		echo "Model of the third most commun cost function ${split[4]}:"
		echo 
		./bin/print_model "${split[4]}"
fi
