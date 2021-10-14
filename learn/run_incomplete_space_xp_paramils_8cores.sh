#!/bin/bash

samples=10000

ad_n=12
ad_d=12

cm_n=12
cm_d=12
cm_p=6

lt_n=12
lt_d=12

le_n=12
le_d=12
le_p=42

ll_n=12
ll_d=12
ll_p=42

lg_n=12
lg_d=12
lg_p=42

ol_n=8
ol_d=32
ol_p=3

hyperparameter="--tournament 2 --pop 100 --steady 10 --mingen 50 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-100-10-50-0.4-1.0-0.17"

for i in {1..12}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_01.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_02.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_03.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_04.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_05.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_06.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_07.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_05.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_06.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_07.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_08.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_08.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_01.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_02.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_03.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_04.txt &

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_01.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_02.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_03.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_04.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_01.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_02.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_03.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_04.txt &

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_01.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_02.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_03.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_04.txt &

wait

(cd results ; cat ad*_0?.txt ad*_1?.txt > ad-${ad_n}-${ad_d}-${samples}-la${suffix}.txt ; rm -f ad*_0?.txt ad*_1?.txt)
(cd results ; cat lt*_0?.txt lt*_1?.txt > lt-${lt_n}-${lt_d}-${samples}-la${suffix}.txt ; rm -f lt*_0?.txt lt*_1?.txt)
(cd results ; cat le*_0?.txt le*_1?.txt > le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}.txt ; rm -f le*_0?.txt le*_1?.txt)
(cd results ; cat ol*_0?.txt ol*_1?.txt > ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}.txt ; rm -f ol*_0?.txt ol*_1?.txt)

wait

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_04.txt &

./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_01.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_02.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_03.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -i spaces/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la.txt --xp "$hyperparameter" >> ./results/ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}_04.txt &

./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_01.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_02.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_03.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -i spaces/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la.txt --xp "$hyperparameter" >> ./results/lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}_04.txt &

wait

(cd results ; cat cm*_0?.txt cm*_1?.txt > cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}.txt ; rm -f cm*_0?.txt cm*_1?.txt)
(cd results ; cat ll*_0?.txt ll*_1?.txt > ll-${ll_n}-${ll_d}-${samples}-${ll_p}-la${suffix}.txt ; rm -f ll*_0?.txt ll*_1?.txt)
(cd results ; cat lg*_0?.txt lg*_1?.txt > lg-${lg_n}-${lg_d}-${samples}-${lg_p}-la${suffix}.txt ; rm -f lg*_0?.txt lg*_1?.txt)
