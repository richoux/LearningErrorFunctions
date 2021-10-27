#!/bin/bash

date=$(date +%Y-%m-%d)

mkdir -p results/"$date"

for i in {1..100}; do
    ./bin/magic_square_fastforward 15 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_15.txt &
    ./bin/magic_square_hardcoded 15 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_15.txt &
    ./bin/magic_square_csp 15 10 2> /dev/null >> ./results/"$date"/magic_square_csp_15.txt &

		./bin/magic_square_fastforward 20 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_20.txt &
    ./bin/magic_square_hardcoded 20 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_20.txt &
    ./bin/magic_square_csp 20 10 2> /dev/null >> ./results/"$date"/magic_square_csp_20.txt &

    # ./bin/magic_square_fastforward 25 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_25.txt &
    # ./bin/magic_square_hardcoded 25 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_25.txt &
    # ./bin/magic_square_csp 25 10 2> /dev/null >> ./results/"$date"/magic_square_csp_25.txt &

		# ./bin/magic_square_fastforward 26 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_26.txt &
    # ./bin/magic_square_hardcoded 26 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_26.txt &
    # ./bin/magic_square_csp 26 10 2> /dev/null >> ./results/"$date"/magic_square_csp_26.txt &

		# ./bin/magic_square_fastforward 27 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_27.txt &
    # ./bin/magic_square_hardcoded 27 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_27.txt &
    # ./bin/magic_square_csp 27 10 2> /dev/null >> ./results/"$date"/magic_square_csp_27.txt &

		# ./bin/magic_square_fastforward 28 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_28.txt &
    # ./bin/magic_square_hardcoded 28 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_28.txt &
    # ./bin/magic_square_csp 28 10 2> /dev/null >> ./results/"$date"/magic_square_csp_28.txt &

		# ./bin/magic_square_fastforward 29 10 2> /dev/null >> ./results/"$date"/magic_square_fastforward_29.txt &
    # ./bin/magic_square_hardcoded 29 10 2> /dev/null >> ./results/"$date"/magic_square_hardcoded_29.txt &
    # ./bin/magic_square_csp 29 10 2> /dev/null >> ./results/"$date"/magic_square_csp_29.txt &
		wait
done
