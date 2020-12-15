#!/bin/bash

echo "WARNING! Bash is doing a lot of float arithmetic errors!"
echo "The solution ratio between parenthesis is just to get an idea."
echo ""

for file in $(ls spaces/complete*)
do
	total=$(wc -l $file | awk '{print $1}')
	solutions=$(grep -E '1 :' $file | wc -l)
	ratio_head=$(((100*$solutions)/$total))
	ratio_tail=$((((100000*$solutions)/$total)-($ratio_head*1000)))
	echo "$file: $solutions/$total ($ratio_head.$ratio_tail)"
done
