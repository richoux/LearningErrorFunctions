#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p killer_sudoku/results/"$date"

for i in {1..6}; do
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_01.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_02.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_03.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_04.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_05.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_06.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_07.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_08.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_09.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_10.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_11.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_12.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_13.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_14.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_15.txt &
    ./killer_sudoku/bin/killer_sudoku_csp 3 60 2> /dev/null >> 3_killer_sudoku_csp_16.txt &
		wait
done

for i in {1..6}; do
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_01.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_02.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_03.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_04.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_05.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_06.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_07.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_08.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_09.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_10.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_11.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_12.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_13.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_14.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_15.txt &
    ./killer_sudoku/bin/killer_sudoku_fastforward 3 60 2> /dev/null >> 3_killer_sudoku_fastforward_16.txt &
		wait
done

for i in {1..6}; do
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_01.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_02.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_03.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_04.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_05.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_06.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_07.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_08.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_09.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_10.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_11.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_12.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_13.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_14.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_15.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_16.txt &
		wait
done

for i in {1..6}; do
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_01.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_02.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_03.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_04.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_05.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_06.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_07.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_08.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_09.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_10.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_11.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_12.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_13.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_14.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_15.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_16.txt &
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

		./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_01.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_02.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_03.txt &
    ./killer_sudoku/bin/killer_sudoku_hardcoded 3 60 2> /dev/null >> 3_killer_sudoku_hardcoded_04.txt &

		./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_01.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_02.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_03.txt &
    ./killer_sudoku/bin/killer_sudoku_handmade 3 60 2> /dev/null >> 3_killer_sudoku_handmade_04.txt &

		wait

		cat 3_killer_sudoku_csp_0?.txt 3_killer_sudoku_csp_1?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_csp.txt ; rm -f 3_killer_sudoku_csp_0?.txt 3_killer_sudoku_csp_1?.txt;
		cat 3_killer_sudoku_fastforward_0?.txt 3_killer_sudoku_fastforward_1?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_fastforward.txt ; rm -f 3_killer_sudoku_fastforward_0?.txt 3_killer_sudoku_fastforward_1?.txt;
		cat 3_killer_sudoku_hardcoded_0?.txt 3_killer_sudoku_hardcoded_1?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_hardcoded.txt ; rm -f 3_killer_sudoku_hardcoded_0?.txt 3_killer_sudoku_hardcoded_1?.txt;
		cat 3_killer_sudoku_handmade_0?.txt 3_killer_sudoku_handmade_1?.txt > killer_sudoku/results/"$date"/3_killer_sudoku_handmade.txt ; rm -f 3_killer_sudoku_handmade_0?.txt 3_killer_sudoku_handmade_1?.txt
