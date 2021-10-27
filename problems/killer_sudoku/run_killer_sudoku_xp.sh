#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p results/"$date"

for i in {1..100}; do
    ./bin/killer_sudoku_fastforward 3 10 2> /dev/null >> ./results/"$date"/3_killer_sudoku_fastforward.txt &
    ./bin/killer_sudoku_hardcoded 3 10 2> /dev/null >> ./results/"$date"/3_killer_sudoku_hardcoded.txt &
    ./bin/killer_sudoku_handmade 3 10 2> /dev/null >> ./results/"$date"/3_killer_sudoku_handmade.txt &
    ./bin/killer_sudoku_csp 3 10 2> /dev/null >> ./results/"$date"/3_killer_sudoku_csp.txt &
		wait
done
