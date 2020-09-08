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
unset IFS
		
sorted_solutions=$(for k in "${!solutions[@]}"
do
    echo $k ${solutions[$k]}
done |
sort -rn -k2)

echo "${sorted_solutions[@]}"

filename=${1%.*}

IFS=- read var1 var2 var3 var4 var5 <<< $filename
unset IFS

if [[ $var1 == *"complete"* ]]; then
		nb_var=${var3}
		domain_size=${var4}
		space_size=$((domain_size ** nb_var))
else
		space_size=$((2*$var4))
fi
echo "space_size = $space_size"

declare -a costs
for val in $(cat costfile); do
		val=${val%.*}
		costs=("${costs[@]}" $val)
done
rm -f costfile

IFS=$'\n' sorted_costs=($(sort -g <<<"${costs[*]}"))
unset IFS

# echo ${sorted_costs[@]} 
# echo ${costs[@]} 
# plop=$(for i in ${costs[@]}; do echo $i; done)
# echo $plop | tr " " ", "

med=$(for i in ${sorted_costs[@]}; do echo $i; done | awk -f median.awk)
med_norm=$(bc <<<"scale=2;$med/$space_size")
echo "Median: $med_norm"

mean=$(for i in ${costs[@]}; do echo $i; done | awk '{sum+=$1} END {print sum/NR}')
mean_norm=$(bc <<<"scale=2;$mean/$space_size")
echo "Mean: $mean_norm"

std_dev=$(for i in ${costs[@]}; do echo $i; done | awk -v mean=$mean '{sum+=$1; sumsq+=$1*$1} END {print sqrt((mean*mean*NR - 2*mean*sum + sumsq)/(NR-1))}')
std_dev_norm=$(bc <<<"scale=2;$std_dev/$space_size")
echo "Sample standard deviation: $std_dev_norm"

split=(${sorted_solutions[@]})

cost_best=$(grep ${split[0]} $1 | awk '{sum += $1} END {print sum/NR}')
cost_best_norm=$(bc <<<"scale=2;$cost_best/$space_size")
echo 
echo "//////////"
echo "Cost of the most commun cost function ${split[0]}: $cost_best_norm"
echo "Model of the most commun cost function ${split[0]}:"
echo 
./bin/print_model "${split[0]}"

# if [[ ${split[2]} ]]; then
# 		echo 
# 		echo "//////////"
# 		echo "Model of the second most commun cost function ${split[2]}:"
# 		echo 
# 		./bin/print_model "${split[2]}"
# fi

# if [[ ${split[4]} ]]; then
# 		echo 
# 		echo "//////////"
# 		echo "Model of the third most commun cost function ${split[4]}:"
# 		echo 
# 		./bin/print_model "${split[4]}"
# fi
