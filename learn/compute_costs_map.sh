#!/bin/bash

for file in $(ls spaces)
do
		filename=${file%.*}

		IFS=- read start nb_vars end <<< $filename
		unset IFS
		
		if ! [[ $start == *"repart"* ]] && ! [[ $end == *"_data"* ]]
		then
				echo "Generating costs map for ${file}"
				output="${filename}_costs.txt"
				if [[ $start == *"complete"* ]]
				then
						./bin/compute_costs_map -n "$nb_vars" -ci "spaces/${file}" -o "spaces/${output}"
						#echo "-n $nb_vars -ci ${file} -o ${output}"
 				else
						./bin/compute_costs_map -n "$nb_vars" -i "spaces/${file}" -o "spaces/${output}"
						#echo "-n $nb_vars -i ${file} -o ${output}"
				fi
				#echo ""
		fi
done
