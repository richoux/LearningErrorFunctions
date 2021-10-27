#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p sudoku/results/"$date"

for i in {1..12}; do
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_01.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_02.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_03.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_04.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_05.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_06.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_07.txt &
    ./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_01.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_02.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_03.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_04.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_05.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_06.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_07.txt &
    ./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_01.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_02.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_03.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_04.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_05.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_06.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_07.txt &
    ./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_01.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_02.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_03.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_04.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_05.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_06.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_07.txt &
    ./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_01.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_02.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_03.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_04.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_05.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_06.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_07.txt &
    ./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_01.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_02.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_03.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_04.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_05.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_06.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_07.txt &
    ./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_01.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_02.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_03.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_04.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_05.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_06.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_07.txt &
    ./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_01.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_02.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_03.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_04.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_05.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_06.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_07.txt &
    ./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_01.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_02.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_03.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_04.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_05.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_06.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_07.txt &
    ./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_01.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_02.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_03.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_04.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_05.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_06.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_07.txt &
    ./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_01.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_02.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_03.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_04.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_05.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_06.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_07.txt &
    ./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_08.txt &
		wait
done

for i in {1..12}; do
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_01.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_02.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_03.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_04.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_05.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_06.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_07.txt &
    ./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_08.txt &
		wait
done

./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_01.txt &
./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_02.txt &
./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_03.txt &
./sudoku/bin/sudoku_csp 3 60 2> /dev/null >> 3_sudoku_csp_04.txt &

./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_01.txt &
./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_02.txt &
./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_03.txt &
./sudoku/bin/sudoku_csp 4 60 2> /dev/null >> 4_sudoku_csp_04.txt &

wait

./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_01.txt &
./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_02.txt &
./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_03.txt &
./sudoku/bin/sudoku_csp 5 60 2> /dev/null >> 5_sudoku_csp_04.txt &

./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_01.txt &
./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_02.txt &
./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_03.txt &
./sudoku/bin/sudoku_fastforward 3 60 2> /dev/null >> 3_sudoku_fastforward_04.txt &

wait

./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_01.txt &
./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_02.txt &
./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_03.txt &
./sudoku/bin/sudoku_fastforward 4 60 2> /dev/null >> 4_sudoku_fastforward_04.txt &

./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_01.txt &
./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_02.txt &
./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_03.txt &
./sudoku/bin/sudoku_fastforward 5 60 2> /dev/null >> 5_sudoku_fastforward_04.txt &

wait

./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_01.txt &
./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_02.txt &
./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_03.txt &
./sudoku/bin/sudoku_hardcoded 3 60 2> /dev/null >> 3_sudoku_hardcoded_04.txt &

./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_01.txt &
./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_02.txt &
./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_03.txt &
./sudoku/bin/sudoku_hardcoded 4 60 2> /dev/null >> 4_sudoku_hardcoded_04.txt &

wait

./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_01.txt &
./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_02.txt &
./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_03.txt &
./sudoku/bin/sudoku_hardcoded 5 60 2> /dev/null >> 5_sudoku_hardcoded_04.txt &

./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_01.txt &
./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_02.txt &
./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_03.txt &
./sudoku/bin/sudoku_handmade 3 60 2> /dev/null >> 3_sudoku_handmade_04.txt &

wait

./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_01.txt &
./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_02.txt &
./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_03.txt &
./sudoku/bin/sudoku_handmade 4 60 2> /dev/null >> 4_sudoku_handmade_04.txt &

./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_01.txt &
./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_02.txt &
./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_03.txt &
./sudoku/bin/sudoku_handmade 5 60 2> /dev/null >> 5_sudoku_handmade_04.txt &

wait

cat 3_sudoku_csp_0?.txt > sudoku/results/"$date"/3_sudoku_csp.txt ; rm -f 3_sudoku_csp_0?.txt
cat 4_sudoku_csp_0?.txt > sudoku/results/"$date"/4_sudoku_csp.txt ; rm -f 4_sudoku_csp_0?.txt
cat 5_sudoku_csp_0?.txt > sudoku/results/"$date"/5_sudoku_csp.txt ; rm -f 5_sudoku_csp_0?.txt

cat 3_sudoku_fastforward_0?.txt > sudoku/results/"$date"/3_sudoku_fastforward.txt ; rm -f 3_sudoku_fastforward_0?.txt
cat 4_sudoku_fastforward_0?.txt > sudoku/results/"$date"/4_sudoku_fastforward.txt ; rm -f 4_sudoku_fastforward_0?.txt
cat 5_sudoku_fastforward_0?.txt > sudoku/results/"$date"/5_sudoku_fastforward.txt ; rm -f 5_sudoku_fastforward_0?.txt

cat 3_sudoku_hardcoded_0?.txt > sudoku/results/"$date"/3_sudoku_hardcoded.txt ; rm -f 3_sudoku_hardcoded_0?.txt
cat 4_sudoku_hardcoded_0?.txt > sudoku/results/"$date"/4_sudoku_hardcoded.txt ; rm -f 4_sudoku_hardcoded_0?.txt
cat 5_sudoku_hardcoded_0?.txt > sudoku/results/"$date"/5_sudoku_hardcoded.txt ; rm -f 5_sudoku_hardcoded_0?.txt

cat 3_sudoku_handmade_0?.txt > sudoku/results/"$date"/3_sudoku_handmade.txt ; rm -f 3_sudoku_handmade_0?.txt 
cat 4_sudoku_handmade_0?.txt > sudoku/results/"$date"/4_sudoku_handmade.txt ; rm -f 4_sudoku_handmade_0?.txt 
cat 5_sudoku_handmade_0?.txt > sudoku/results/"$date"/5_sudoku_handmade.txt ; rm -f 5_sudoku_handmade_0?.txt 
