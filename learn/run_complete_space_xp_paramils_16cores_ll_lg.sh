#!/bin/bash

le_n=3
le_d=8
le_p=12

#small
hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17__2"

for i in {1..6}
do
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_04.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_05.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_06.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_07.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_08.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_09.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_10.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_11.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_12.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_13.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_14.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_15.txt &
		./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_16.txt &
		wait
done

for i in {1..6}
do
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_05.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_06.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_07.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_08.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_09.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_10.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_11.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_12.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_13.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_14.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_15.txt &
    ./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_16.txt &
		wait
done

./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
./bin/learn_cf_ga -c ll -n $le_n -d $le_d -p $le_p -ci spaces/complete_ll-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ll-${le_n}-${le_d}-${le_p}${suffix}_04.txt &

./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
./bin/learn_cf_ga -c lg -n $le_n -d $le_d -p $le_p -ci spaces/complete_lg-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-lg-${le_n}-${le_d}-${le_p}${suffix}_04.txt &

wait

(cd results/complete ; cat complete-ll*_0?.txt complete-ll*_1?.txt > complete-ll-${le_n}-${le_d}-${le_p}${suffix}.txt ; rm -f complete-ll*_0?.txt complete-ll*_1?.txt)
(cd results/complete ; cat complete-lg*_0?.txt complete-lg*_1?.txt > complete-lg-${le_n}-${le_d}-${le_p}${suffix}.txt ; rm -f complete-lg*_0?.txt complete-lg*_1?.txt)
