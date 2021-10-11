#!/bin/bash

ad_n=4
ad_d=5

cm_n=4
cm_d=5
cm_p=3

#small
hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17__2"

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

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_01.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_02.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_03.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_04.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_04.txt &

wait

(cd results/complete ; cat complete-ad*_0?.txt complete-ad*_1?.txt > complete-ad-${ad_n}-${ad_d}${suffix}.txt ; rm -f complete-ad*_0?.txt complete-ad*_1?.txt)
(cd results/complete ; cat complete-cm*_0?.txt complete-cm*_1?.txt > complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}.txt ; rm -f complete-cm*_0?.txt complete-cm*_1?.txt)
