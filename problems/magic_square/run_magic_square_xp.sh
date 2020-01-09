#!/bin/bash


for i in {1..100}; do
    ./bin/magic_square 4 >> ./results/magic_square.txt &
    ./bin/magic_square_handmade 4 >> ./results/magic_square_handmade.txt &
    ./bin/magic_square_nocfn 4 >> ./results/magic_square_nocfn.txt &
		wait
done
