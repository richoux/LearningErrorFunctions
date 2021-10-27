#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p magic_square/results/"$date"

for i in {1..6}; do
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_04.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_05.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_06.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_07.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_08.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_09.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_10.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_11.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_12.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_13.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_14.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_15.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_04.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_05.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_06.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_07.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_08.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_09.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_10.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_11.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_12.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_13.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_14.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_15.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_04.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_05.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_06.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_07.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_08.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_09.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_10.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_11.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_12.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_13.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_14.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_15.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_04.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_05.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_06.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_07.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_08.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_09.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_10.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_11.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_12.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_13.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_14.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_15.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_04.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_05.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_06.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_07.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_08.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_09.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_10.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_11.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_12.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_13.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_14.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_15.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_04.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_05.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_06.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_07.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_08.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_09.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_10.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_11.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_12.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_13.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_14.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_15.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_04.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_05.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_06.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_07.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_08.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_09.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_10.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_11.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_12.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_13.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_14.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_15.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_04.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_05.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_06.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_07.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_08.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_09.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_10.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_11.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_12.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_13.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_14.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_15.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_16.txt &
		wait
done

for i in {1..6}; do
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_04.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_05.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_06.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_07.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_08.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_09.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_10.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_11.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_12.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_13.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_14.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_15.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_16.txt &
		wait
done

    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 15 60 2> /dev/null >> 15_magic_square_csp_04.txt &

    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 20 60 2> /dev/null >> 20_magic_square_csp_04.txt &

		./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_04.txt &

		./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 15 60 2> /dev/null >> 15_magic_square_fastforward_04.txt &

		wait

		./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 20 60 2> /dev/null >> 20_magic_square_fastforward_04.txt &

		./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_04.txt &

		./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 15 60 2> /dev/null >> 15_magic_square_hardcoded_04.txt &

		./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 20 60 2> /dev/null >> 20_magic_square_hardcoded_04.txt &

		wait

		./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_04.txt &

		wait

		cat 15_magic_square_csp_0?.txt 15_magic_square_csp_1?.txt > magic_square/results/"$date"/15_magic_square_csp.txt ; rm -f 15_magic_square_csp_0?.txt 15_magic_square_csp_1?.txt;
		cat 20_magic_square_csp_0?.txt 20_magic_square_csp_1?.txt > magic_square/results/"$date"/20_magic_square_csp.txt ; rm -f 20_magic_square_csp_0?.txt 20_magic_square_csp_1?.txt;
		cat 25_magic_square_csp_0?.txt 25_magic_square_csp_1?.txt > magic_square/results/"$date"/25_magic_square_csp.txt ; rm -f 25_magic_square_csp_0?.txt 25_magic_square_csp_1?.txt;

		cat 15_magic_square_fastforward_0?.txt 15_magic_square_fastforward_1?.txt > magic_square/results/"$date"/15_magic_square_fastforward.txt ; rm -f 15_magic_square_fastforward_0?.txt 15_magic_square_fastforward_1?.txt;
		cat 20_magic_square_fastforward_0?.txt 20_magic_square_fastforward_1?.txt > magic_square/results/"$date"/20_magic_square_fastforward.txt ; rm -f 20_magic_square_fastforward_0?.txt 20_magic_square_fastforward_1?.txt;
		cat 25_magic_square_fastforward_0?.txt 25_magic_square_fastforward_1?.txt > magic_square/results/"$date"/25_magic_square_fastforward.txt ; rm -f 25_magic_square_fastforward_0?.txt 25_magic_square_fastforward_1?.txt;

		cat 15_magic_square_hardcoded_0?.txt 15_magic_square_hardcoded_1?.txt > magic_square/results/"$date"/15_magic_square_hardcoded.txt ; rm -f 15_magic_square_hardcoded_0?.txt 15_magic_square_hardcoded_1?.txt;
		cat 20_magic_square_hardcoded_0?.txt 20_magic_square_hardcoded_1?.txt > magic_square/results/"$date"/20_magic_square_hardcoded.txt ; rm -f 20_magic_square_hardcoded_0?.txt 20_magic_square_hardcoded_1?.txt;
		cat 25_magic_square_hardcoded_0?.txt 25_magic_square_hardcoded_1?.txt > magic_square/results/"$date"/25_magic_square_hardcoded.txt ; rm -f 25_magic_square_hardcoded_0?.txt 25_magic_square_hardcoded_1?.txt
