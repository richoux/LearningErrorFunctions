#!/bin/bash

IFS=$'\n'
for line in $(cat "$1")
do
		# echo "$count"
		# echo "$line"
		#echo [[ "$line" =~ ^[WARN.* ]]
		if ! [[ "$line" == "[WARN"* ]]
		then
			 echo "$line"
		fi
done
unset IFS
