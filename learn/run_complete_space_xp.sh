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

for i in {1..12}
do
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_1.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_2.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_3.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_4.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_5.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_6.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_7.txt &
		./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_1.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_2.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_3.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_4.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_5.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_6.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_7.txt &
    ./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_1.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_2.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_3.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_4.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_5.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_6.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_7.txt &
    ./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_1.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_2.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_3.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_4.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_5.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_6.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_7.txt &
    ./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_8.txt &
		wait
done

for i in {1..12}
do
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_1.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_2.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_3.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_4.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_5.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_6.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_7.txt &
    ./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_8.txt &
		wait
done

./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_1.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_2.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_3.txt &
./bin/learn_cf_ga -c ad -n $ad_n -d $ad_d -ci spaces/complete_ad-${ad_n}-${ad_d}.txt --xp >> ./results/complete/complete-ad-${ad_n}-${ad_d}_4.txt &

./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_1.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_2.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_3.txt &
./bin/learn_cf_ga -c cm -n $cm_n -d $cm_d -p $cm_p -ci spaces/complete_cm-${cm_n}-${cm_d}-${cm_p}.txt --xp >> ./results/complete/complete-cm-${cm_n}-${cm_d}-${cm_p}_4.txt &

wait

./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_1.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_2.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_3.txt &
./bin/learn_cf_ga -c lt -n $lt_n -d $lt_d -ci spaces/complete_lt-${lt_n}-${lt_d}.txt --xp >> ./results/complete/complete-lt-${lt_n}-${lt_d}_4.txt &

./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_1.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_2.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_3.txt &
./bin/learn_cf_ga -c le -n $le_n -d $le_d -p $le_p -ci spaces/complete_le-${le_n}-${le_d}-${le_p}.txt --xp >> ./results/complete/complete-le-${le_n}-${le_d}-${le_p}_4.txt &

wait

./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_1.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_2.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_3.txt &
./bin/learn_cf_ga -c ol -n $ol_n -d $ol_d -p $ol_p -ci spaces/complete_ol-${ol_n}-${ol_d}-${ol_p}.txt --xp >> ./results/complete/complete-ol-${ol_n}-${ol_d}-${ol_p}_4.txt &

wait

(cd results/complete ; cat complete-ad*_?.txt > complete-ad-${ad_n}-${ad_d}.txt ; rm -f complete-ad*_?.txt)
(cd results/complete ; cat complete-cm*_?.txt > complete-cm-${cm_n}-${cm_d}-${cm_p}.txt ; rm -f complete-cm*_?.txt)
(cd results/complete ; cat complete-lt*_?.txt > complete-lt-${lt_n}-${lt_d}.txt ; rm -f complete-lt*_?.txt)
(cd results/complete ; cat complete-le*_?.txt > complete-le-${le_n}-${le_d}-${le_p}.txt ; rm -f complete-le*_?.txt)
(cd results/complete ; cat complete-ol*_?.txt > complete-ol-${ol_n}-${ol_d}-${ol_p}.txt ; rm -f complete-ol*_?.txt)
