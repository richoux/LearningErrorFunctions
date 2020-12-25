#!/bin/bash

ad_n=5
ad_d=5

cm_n=3
cm_d=11
cm_p=8

lt_n=5
lt_d=5

le_n=3
le_d=11
le_p=23

ol_n=3
ol_d=8
ol_p=3

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
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_1.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_2.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_3.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_4.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_5.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_6.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_7.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_1.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_2.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_3.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_4.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_5.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_6.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_7.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_1.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_2.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_3.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_4.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_5.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_6.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_7.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_1.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_2.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_3.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_4.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_5.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_6.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_7.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_1.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_2.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_3.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_4.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_5.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_6.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_7.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_8.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_1.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_2.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_3.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-ad-${ad_n}-${ad_d}${suffix}_4.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_1.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_2.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_3.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}_4.txt &

wait

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_1.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_2.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_3.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp "$hyperparameter" >> ./results/complete/complete-lt-${lt_n}-${lt_d}${suffix}_4.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_1.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_2.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_3.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}${suffix}_4.txt &

wait

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_1.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_2.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_3.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp "$hyperparameter" >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}_4.txt &

wait

(cd results/complete ; cat complete-ad*_?.txt > complete-ad-${ad_n}-${ad_d}${suffix}.txt ; rm -f complete-ad*_?.txt)
(cd results/complete ; cat complete-cm*_?.txt > complete-cm-${cm_n}-${cm_d}-${cm_p}${suffix}.txt ; rm -f complete-cm*_?.txt)
(cd results/complete ; cat complete-lt*_?.txt > complete-lt-${lt_n}-${lt_d}${suffix}.txt ; rm -f complete-lt*_?.txt)
(cd results/complete ; cat complete-le*_?.txt > complete-le-${le_n}-${le_d}-${le_p}${suffix}.txt ; rm -f complete-le*_?.txt)
(cd results/complete ; cat complete-ol*_?.txt > complete-ol-${ol_n}-${ol_d}-${ol_p}${suffix}.txt ; rm -f complete-ol*_?.txt)
