#!/bin/bash

samples=10000

cm_n=12
cm_d=12
cm_p=6

hyperparameter="--tournament 2 --pop 100 --steady 10 --mingen 50 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-100-10-50-0.4-1.0-0.17"

for i in {1..12}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_05.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_06.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_07.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_08.txt &
		wait
done

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_01.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_02.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_03.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -i spaces/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la.txt --xp "$hyperparameter" >> ./results/cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}_04.txt &

wait

(cd results ; cat cm*_0?.txt > cm-${cm_n}-${cm_d}-${samples}-${cm_p}-la${suffix}.txt ; rm -f cm*_0?.txt)
