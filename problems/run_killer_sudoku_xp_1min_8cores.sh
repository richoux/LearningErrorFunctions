#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p killer_sudoku/results/"$date"

for i in {1..12}; do
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_01.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_02.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_03.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_04.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_05.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_06.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_07.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_01.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_02.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_03.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_04.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_05.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_06.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_07.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_01.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_02.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_03.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_04.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_05.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_06.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_07.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_08.txt &
		wait
done

for i in {1..12}; do
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_01.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_02.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_03.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_04.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_05.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_06.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_07.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_08.txt &
		wait
done

./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_01.txt &
./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_02.txt &
./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_03.txt &
./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_04.txt &

./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_01.txt &
./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_02.txt &
./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_03.txt &
./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_04.txt &

wait

./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_01.txt &
./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_02.txt &
./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_03.txt &
./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_04.txt &

./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_01.txt &
./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_02.txt &
./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_03.txt &
./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_04.txt &

wait

cat 3_killer_sudoku_csp_0?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_csp.txt ; rm -f 3_killer_sudoku_csp_0?.txt 
cat 3_killer_sudoku_fastforward_0?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_fastforward.txt ; rm -f 3_killer_sudoku_fastforward_0?.txt 
cat 3_killer_sudoku_hardcoded_0?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_hardcoded.txt ; rm -f 3_killer_sudoku_hardcoded_0?.txt 
cat 3_killer_sudoku_handmade_0?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_handmade.txt ; rm -f 3_killer_sudoku_handmade_0?.txt 
