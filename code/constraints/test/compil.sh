#!/bin/bash

if [ "$1" == "LATIN" ]
then
		echo "g++ -I../../latin/ -DLATIN random_draw.cpp ../../latin/latin.cpp -o random_draw -lghost"
		g++ -I../../latin/ -DLATIN random_draw.cpp ../../latin/latin.cpp -o random_draw -lghost
else
		echo "g++ -I../../latin/ random_draw.cpp ../../latin/latin.cpp -o random_draw -lghost"
		g++ -I../../latin/ random_draw.cpp ../../latin/latin.cpp -o random_draw -lghost
fi
