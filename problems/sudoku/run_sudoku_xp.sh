#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p results/"$date"

for i in {1..100}; do
    ./bin/sudoku 2> /dev/null >> ./results/"$date"/3_sudoku.txt &
    ./bin/sudoku_hardcoded 2> /dev/null >> ./results/"$date"/3_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 2> /dev/null >> ./results/"$date"/3_sudoku_handmade.txt &
    ./bin/sudoku_nocfn 2> /dev/null >> ./results/"$date"/3_sudoku_nocfn.txt &

    ./bin/sudoku 4 2> /dev/null >> ./results/"$date"/4_sudoku.txt &
    ./bin/sudoku_hardcoded 4 2> /dev/null >> ./results/"$date"/4_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 4 2> /dev/null >> ./results/"$date"/4_sudoku_handmade.txt &
    ./bin/sudoku_nocfn 4 2> /dev/null >> ./results/"$date"/4_sudoku_nocfn.txt &

		./bin/sudoku 5 2> /dev/null >> ./results/"$date"/5_sudoku.txt &
    ./bin/sudoku_hardcoded 5 2> /dev/null >> ./results/"$date"/5_sudoku_hardcoded.txt &
    ./bin/sudoku_handmade 5 2> /dev/null >> ./results/"$date"/5_sudoku_handmade.txt &
    ./bin/sudoku_nocfn 5 2> /dev/null >> ./results/"$date"/5_sudoku_nocfn.txt &
		wait
done
