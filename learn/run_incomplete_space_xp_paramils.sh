#!/bin/bash

samples=1000

ad_n=6
ad_d=6

cm_n=6
cm_d=6
cm_p=3

lt_n=6
lt_d=6

le_n=6
le_d=6
le_p=12

ol_n=6
ol_d=18
ol_p=2

# ad_n=4
# ad_d=5

# cm_n=4
# cm_d=5
# cm_p=3

# lt_n=4
# lt_d=5

# le_n=3
# le_d=8
# le_p=12

# ol_n=3
# ol_d=8
# ol_p=2

#large
# hyperparameter="--tournament 2 --pop 200 --steady 25 --mingen 600 --crossover 0.4 --mutation 0.6 --replacement 0.03"
# suffix="_paramils_large_2-200-25-600-0.4-0.6-0.03"

#small
hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17"

for i in {1..12}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_1.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_2.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_3.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_4.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_5.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_6.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_7.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_1.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_2.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_3.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_4.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_5.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_6.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_7.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_1.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_2.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_3.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_4.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_5.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_6.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_7.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_1.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_2.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_3.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_4.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_5.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_6.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_7.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_1.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_2.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_3.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_4.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_5.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_6.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_7.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_8.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_1.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_2.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_3.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_4.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_1.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_2.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_3.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_4.txt &

wait

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_1.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_2.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_3.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_4.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_1.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_2.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_3.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_4.txt &

wait

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_1.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_2.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_3.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_4.txt &

wait

(cd results ; cat ad*_?.txt > ad-${ad_n}-${ad_d}-${samples}-la${suffix}.txt ; rm -f ad*_?.txt)
(cd results ; cat cm*_?.txt > cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}.txt ; rm -f cm*_?.txt)
(cd results ; cat lt*_?.txt > lt-${lt_n}-${lt_d}-${samples}-la${suffix}.txt ; rm -f lt*_?.txt)
(cd results ; cat le*_?.txt > le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}.txt ; rm -f le*_?.txt)
(cd results ; cat ol*_?.txt > ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}.txt ; rm -f ol*_?.txt)
