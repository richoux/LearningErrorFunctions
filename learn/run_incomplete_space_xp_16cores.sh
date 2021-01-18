#!/bin/bash

samples=1000
#samples=10000

ad_n=12
ad_d=12

cm_n=12
cm_d=12
cm_p=6

lt_n=12
lt_d=12

le_n=12
le_d=12
le_p=72

ol_n=8
ol_d=32
ol_p=3

for i in {1..6}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_01.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_02.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_03.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_04.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_05.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_06.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_07.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_08.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_09.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_10.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_11.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_12.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_13.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_14.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_15.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_05.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_06.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_07.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_08.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_09.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_10.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_11.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_12.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_13.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_14.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_15.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_01.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_02.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_03.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_04.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_05.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_06.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_07.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_08.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_09.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_10.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_11.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_12.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_13.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_14.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_15.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_01.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_02.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_03.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_04.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_05.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_06.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_07.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_08.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_09.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_10.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_11.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_12.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_13.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_14.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_15.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_01.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_02.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_03.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_04.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_05.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_06.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_07.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_08.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_09.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_10.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_11.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_12.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_13.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_14.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_15.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_16.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_01.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_02.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_03.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp >> ./results/ad-${ad_n}-${ad_d}-${samples}-la_04.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc_04.txt &

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_01.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_02.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_03.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp >> ./results/lt-${lt_n}-${lt_d}-${samples}-la_04.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_01.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_02.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_03.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la_04.txt &

wait

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_01.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_02.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_03.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la_04.txt &

wait

(cd results ; cat ad*_0?.txt ad*_1?.txt > ad-${ad_n}-${ad_d}-${samples}-la.txt ; rm -f ad*_0?.txt ad*_1?.txt)
(cd results ; cat cm*_0?.txt cm*_1?.txt > cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt ; rm -f cm*_0?.txt cm*_1?.txt)
(cd results ; cat lt*_0?.txt lt*_1?.txt > lt-${lt_n}-${lt_d}-${samples}-la.txt ; rm -f lt*_0?.txt lt*_1?.txt)
(cd results ; cat le*_0?.txt le*_1?.txt > le-${le_n}-${le_d}-${samples}-${le_p}-la.txt ; rm -f le*_0?.txt le*_1?.txt)
(cd results ; cat ol*_0?.txt ol*_1?.txt > ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt ; rm -f ol*_0?.txt ol*_1?.txt)
