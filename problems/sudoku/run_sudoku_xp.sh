#!/bin/bash


for i in {1..100}; do
    ./bin/sudoku >> ./results/sudoku.txt &
    ./bin/sudoku_hardcoded >> ./results/sudoku_hardcoded.txt &
    ./bin/sudoku_handmade >> ./results/sudoku_handmade.txt &
    ./bin/sudoku_nocfn >> ./results/sudoku_nocfn.txt &
		wait
done
