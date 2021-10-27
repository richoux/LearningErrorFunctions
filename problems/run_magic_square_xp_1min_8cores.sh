#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p magic_square/results/"$date"

for i in {1..12}; do
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_04.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_05.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_06.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_07.txt &
    ./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_01.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_02.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_03.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_04.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_05.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_06.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_07.txt &
    ./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_08.txt &
		wait
done

for i in {1..12}; do
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_04.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_05.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_06.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_07.txt &
    ./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_01.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_02.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_03.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_04.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_05.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_06.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_07.txt &
    ./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_08.txt &
		wait
done

for i in {1..12}; do
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_04.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_05.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_06.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_07.txt &
    ./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_08.txt &
		wait
done

for i in {1..12}; do
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_01.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_02.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_03.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_04.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_05.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_06.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_07.txt &
    ./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_08.txt &
		wait
done

./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_01.txt &
./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_02.txt &
./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_03.txt &
./magic_square/bin/magic_square_csp 25 60 2> /dev/null >> 25_magic_square_csp_04.txt &

./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_01.txt &
./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_02.txt &
./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_03.txt &
./magic_square/bin/magic_square_fastforward 25 60 2> /dev/null >> 25_magic_square_fastforward_04.txt &

wait

./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_01.txt &
./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_02.txt &
./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_03.txt &
./magic_square/bin/magic_square_csp 30 60 2> /dev/null >> 30_magic_square_csp_04.txt &

./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_01.txt &
./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_02.txt &
./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_03.txt &
./magic_square/bin/magic_square_fastforward 30 60 2> /dev/null >> 30_magic_square_fastforward_04.txt &

wait

./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_01.txt &
./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_02.txt &
./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_03.txt &
./magic_square/bin/magic_square_hardcoded 25 60 2> /dev/null >> 25_magic_square_hardcoded_04.txt &

./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_01.txt &
./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_02.txt &
./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_03.txt &
./magic_square/bin/magic_square_hardcoded 30 60 2> /dev/null >> 30_magic_square_hardcoded_04.txt &

wait

cat 25_magic_square_csp_0?.txt > magic_square/results/"$date"/25_magic_square_csp.txt ; rm -f 25_magic_square_csp_0?.txt
cat 30_magic_square_csp_0?.txt > magic_square/results/"$date"/30_magic_square_csp.txt ; rm -f 30_magic_square_csp_0?.txt

cat 25_magic_square_fastforward_0?.txt > magic_square/results/"$date"/25_magic_square_fastforward.txt ; rm -f 25_magic_square_fastforward_0?.txt
cat 30_magic_square_fastforward_0?.txt > magic_square/results/"$date"/30_magic_square_fastforward.txt ; rm -f 30_magic_square_fastforward_0?.txt

cat 25_magic_square_hardcoded_0?.txt > magic_square/results/"$date"/25_magic_square_hardcoded.txt ; rm -f 25_magic_square_hardcoded_0?.txt
cat 30_magic_square_hardcoded_0?.txt > magic_square/results/"$date"/30_magic_square_hardcoded.txt ; rm -f 30_magic_square_hardcoded_0?.txt
