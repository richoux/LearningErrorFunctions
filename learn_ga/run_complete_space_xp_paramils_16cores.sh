#!/bin/bash

ad_n=4
ad_d=5

cm_n=4
cm_d=5
cm_p=3

lt_n=4
lt_d=5

le_n=3
le_d=8
le_p=12

ll_n=3
ll_d=8
ll_p=12

lg_n=3
lg_d=8
lg_p=12

ol_n=3
ol_d=8
ol_p=2

hyperparameter="--tournament 2 --pop 100 --steady 10 --mingen 50 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_2-100-10-50-0.4-1.0-0.17"

for i in {1..6}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_01.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_02.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_03.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_04.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_05.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_06.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_07.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_08.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_09.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_10.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_11.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_12.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_13.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_14.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_15.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_01.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_02.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_03.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_04.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_05.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_06.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_07.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_08.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_09.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_10.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_11.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_12.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_13.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_14.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_15.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_16.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_01.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_02.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_03.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_04.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_04.txt &

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_01.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_02.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_03.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_04.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_04.txt &

wait

./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_01.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_02.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_03.txt &
./bin/learn_cf_ga -c ll -n $ll_n -d $ll_d -p $ll_p -ci spaces/complete_ll-${ll_n}-${ll_d}-${ll_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}_04.txt &

./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_01.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_02.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_03.txt &
./bin/learn_cf_ga -c lg -n $lg_n -d $lg_d -p $lg_p -ci spaces/complete_lg-${lg_n}-${lg_d}-${lg_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}_04.txt &

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_01.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_02.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_03.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_04.txt &

wait

(cd results/complete ; cat complete-ad*_0?.txt complete-ad*_1?.txt > complete-ad-${ad_n}-${ad_d}${suffix}.txt ; rm -f complete-ad*_0?.txt complete-ad*_1?.txt)
(cd results/complete ; cat complete-cm*_0?.txt complete-cm*_1?.txt > complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}.txt ; rm -f complete-cm*_0?.txt complete-cm*_1?.txt)
(cd results/complete ; cat complete-lt*_0?.txt complete-lt*_1?.txt > complete-lt-${lt_n}-${lt_d}${suffix}.txt ; rm -f complete-lt*_0?.txt complete-lt*_1?.txt)
(cd results/complete ; cat complete-le*_0?.txt complete-le*_1?.txt > complete-le-${le_n}-${le_d}-${le_p}${suffix}.txt ; rm -f complete-le*_0?.txt complete-le*_1?.txt)
(cd results/complete ; cat complete-ll*_0?.txt complete-ll*_1?.txt > complete-ll-${ll_n}-${ll_d}-${ll_p}${suffix}.txt ; rm -f complete-ll*_0?.txt complete-ll*_1?.txt)
(cd results/complete ; cat complete-lg*_0?.txt complete-lg*_1?.txt > complete-lg-${lg_n}-${lg_d}-${lg_p}${suffix}.txt ; rm -f complete-lg*_0?.txt complete-lg*_1?.txt)
(cd results/complete ; cat complete-ol*_0?.txt complete-ol*_1?.txt > complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}.txt ; rm -f complete-ol*_0?.txt complete-ol*_1?.txt)
