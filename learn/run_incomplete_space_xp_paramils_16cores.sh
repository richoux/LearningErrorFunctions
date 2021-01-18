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

#large
# hyperparameter="--tournament 2 --pop 200 --steady 25 --mingen 600 --crossover 0.4 --mutation 0.6 --replacement 0.03"
# suffix="_paramils_large_2-200-25-600-0.4-0.6-0.03"

#small
hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17"

# for i in {1..6}
# do
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_01.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_02.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_03.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_04.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_05.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_06.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_07.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_08.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_09.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_10.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_11.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_12.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_13.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_14.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_15.txt &
# 		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_16.txt &
# 		wait
# done

for i in {1..6}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_05.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_06.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_07.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_08.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_09.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_10.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_11.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_12.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_13.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_14.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_15.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_16.txt &
		wait
done

# for i in {1..6}
# do
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_01.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_02.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_03.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_04.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_05.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_06.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_07.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_08.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_09.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_10.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_11.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_12.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_13.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_14.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_15.txt &
#     ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_16.txt &
# 		wait
# done

# for i in {1..6}
# do
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_01.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_02.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_03.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_04.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_05.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_06.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_07.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_08.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_09.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_10.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_11.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_12.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_13.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_14.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_15.txt &
#     ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_16.txt &
# 		wait
# done

# for i in {1..6}
# do
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_01.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_02.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_03.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_04.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_05.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_06.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_07.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_08.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_09.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_10.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_11.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_12.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_13.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_14.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_15.txt &
#     ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_16.txt &
# 		wait
# done

# ./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_01.txt &
# ./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_02.txt &
# ./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_03.txt &
# ./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-${samples}-la${suffix}_04.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}_04.txt &

# wait

# ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_01.txt &
# ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_02.txt &
# ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_03.txt &
# ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -i spaces/lt-${lt_n}-${lt_d}-${samples}-la.txt --xp "$hyperparameter" >> ./results/lt-${lt_n}-${lt_d}-${samples}-la${suffix}_04.txt &

# ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_01.txt &
# ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_02.txt &
# ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_03.txt &
# ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -i spaces/le-${le_n}-${le_d}-${samples}-${le_p}-la.txt --xp "$hyperparameter" >> ./results/le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}_04.txt &

# wait

# ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_01.txt &
# ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_02.txt &
# ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_03.txt &
# ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -i spaces/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la.txt --xp "$hyperparameter" >> ./results/ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}_04.txt &

wait

# (cd results ; cat ad*_0?.txt ad*_1?.txt > ad-${ad_n}-${ad_d}-${samples}-la${suffix}.txt ; rm -f ad*_0?.txt ad*_1?.txt)
(cd results ; cat cm*_0?.txt cm*_1?.txt > cm-${cm_n}-${cm_d}-${samples}-${cm_p}-mc${suffix}.txt ; rm -f cm*_0?.txt cm*_1?.txt)
# (cd results ; cat lt*_0?.txt lt*_1?.txt > lt-${lt_n}-${lt_d}-${samples}-la${suffix}.txt ; rm -f lt*_0?.txt lt*_1?.txt)
# (cd results ; cat le*_0?.txt le*_1?.txt > le-${le_n}-${le_d}-${samples}-${le_p}-la${suffix}.txt ; rm -f le*_0?.txt le*_1?.txt)
# (cd results ; cat ol*_0?.txt ol*_1?.txt > ol-${ol_n}-${ol_d}-${samples}-${ol_p}-la${suffix}.txt ; rm -f ol*_0?.txt ol*_1?.txt)
