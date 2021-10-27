#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p results/"$date"

for i in {1..100}; do
    ./bin/sudoku_fastforward 3 10 2> /dev/null >> ./results/"$date"/3_sudoku_fastforward.txt &
    ./bin/sudoku_hardcoded 3 10 2> /dev/null >> ./results/"$date"/3_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 3 10 2> /dev/null >> ./results/"$date"/3_sudoku_handmade.txt &
    ./bin/sudoku_csp 3 10 2> /dev/null >> ./results/"$date"/3_sudoku_csp.txt &

    ./bin/sudoku_fastforward 4 10 2> /dev/null >> ./results/"$date"/4_sudoku_fastforward.txt &
    ./bin/sudoku_hardcoded 4 10 2> /dev/null >> ./results/"$date"/4_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 4 10 2> /dev/null >> ./results/"$date"/4_sudoku_handmade.txt &
    ./bin/sudoku_csp 4 10 2> /dev/null >> ./results/"$date"/4_sudoku_csp.txt &

		./bin/sudoku_fastforward 5 10 2> /dev/null >> ./results/"$date"/5_sudoku_fastforward.txt &
    ./bin/sudoku_hardcoded 5 10 2> /dev/null >> ./results/"$date"/5_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 5 10 2> /dev/null >> ./results/"$date"/5_sudoku_handmade.txt &
    ./bin/sudoku_csp 5 10 2> /dev/null >> ./results/"$date"/5_sudoku_csp.txt &
		wait
done
