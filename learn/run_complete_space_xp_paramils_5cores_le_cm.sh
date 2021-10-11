#!/bin/bash

cm_n=4
cm_d=5
cm_p=3

le_n=3
le_d=8
le_p=12

hyperparameter="--tournament 2 --pop 160 --steady 50 --mingen 800 --crossover 0.4 --mutation 1.0 --replacement 0.17"
suffix="_paramils_small_2-160-50-800-0.4-1.0-0.17__3"

for i in {1..20}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_05.txt &
		wait
done

for i in {1..20}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_01.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_02.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_03.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_04.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_05.txt &
		wait
done

(cd results/complete ; cat complete-cm*_0?.txt complete-cm*_1?.txt > complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}.txt ; rm -f complete-cm*_0?.txt complete-cm*_1?.txt)
(cd results/complete ; cat complete-le*_0?.txt complete-le*_1?.txt > complete-le-${le_n}-${le_d}-${le_p}${suffix}.txt ; rm -f complete-le*_0?.txt complete-le*_1?.txt)
