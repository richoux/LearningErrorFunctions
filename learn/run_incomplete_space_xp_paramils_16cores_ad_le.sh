#!/bin/bash

ad_n=12
ad_d=12

#small
hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17_2"

for i in {1..6}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_01.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_02.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_03.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_04.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_05.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_06.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_07.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_08.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_09.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_10.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_11.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_12.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_13.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_14.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_15.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_16.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_01.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_02.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_03.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -i spaces/ad-${ad_n}-${ad_d}-10000-la.txt --xp "$hyperparameter" >> ./results/ad-${ad_n}-${ad_d}-10000-la${suffix}_04.txt &

wait

(cd results ; cat ad*-10000-*_0?.txt ad*-10000-*_1?.txt > ad-${ad_n}-${ad_d}-10000-la${suffix}.txt ; rm -f ad*-10000-*_0?.txt ad*-10000-*_1?.txt)
