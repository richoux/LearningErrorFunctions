# How to:

## Compile the main program to learn Error Functions

`$> cd learn_cp`  
`$> ./compilation/compile_learn_cp.sh`

<br>
  
## Run the main program to learn Error Functions
/\* in learn_cp folder \*/  
`$> ./bin/learn_cf_cp (and many options, type -h first to have them)`

### For instance
/\* to learn a error function for AllDifferent-4-5 over 1000 Latin hypercube samplings:\*/  
`$> ./bin/learn_cf_cp -c ad -n 4 -d 5 -l -s 1000`

<br>
  
## Run the main program to learn Error Functions using precomputed \*\*incomplete\*\* constraint spaces
/\* in learn folder \*/  
`$> ./bin/learn_cf_cp -i ../learn_ga/spaces/the_file_you_want (plus many other options, type -h first to have them)`

### For instance
/\* to learn a error function from the Ordered-6-9 incomplete constraint space with 100 Latin hypercube samplings:\*/  
/\* 'lt' stands for LessThan, the Ordered constraint implementation we choose for this paper.\*/  
`$> ./bin/learn_cf_cp -c lt -n 6 -d 9 -i ../learn_ga/spaces/lt-6-9-100-la.txt`

<br>
  
## Run the main program to learn Error Functions using precomputed \*\*complete\*\* constraint spaces
/\* in learn folder \*/  
`$> ./bin/learn_cf_cp -ci ../learn_ga/spaces/complete_the_file_you_want (plus many other options, type -h first to have them)`

### For instance
/\* to learn a error function from the LinearSum-3-8-12 complete constraint space:\*/  
/\* 'le' stands for LinearEquation.\*/  
`$> ./bin/learn_cf_cp -c le -n 3 -d 8 -p 12 -ci ../learn_ga/spaces/complete_le-3-8-12.txt`

<br>
  
## Re-run Experiment 1
/\* in learn folder \*/  
`$> ./run_xp_complete.sh (take about two minutes over 16 cores)`

### Warning
This will add new results into result files in the results folder. You need to either change the script or rename the corresponding files.

<br>
  
## Re-run Experiment 2
/\* in learn folder \*/  
`$> ./run_xp_incomplete.sh (take about one night over 16 cores)`

### Warning
This will add new results into result files in the results folder. You need to either change the script or rename the corresponding files.

<br>
  
## Re-run Experiment 3
/\* in problems/xyz folder \*/  
/\* First, compile all models for problem xyz \*/ 
`$> ./compile_all_xyz.sh`

After compiling  Sudoku, Killer Sudoku  and Magic Square,  the fastest
way to run all experiments is to run in the problems folder:
`$> ./run_xp_1mon.sh (take about 2 hours over 16 cores)`

<br>
  
## Analyse result files from Experiments 1 and 2 (this will also print the 3 most frequently learned error functions)
/\* in learn_cp folder \*/  
/\* Compile first the program printing models \*/  
`$> ../learn_ga/compilation/compile_print_model.sh`  
`$> ./analyse_runs.rb results/the_file_you_want`

### For instance
/\* to print results about LinearSum-3-8-12 learned upon the complete constraint space:\*/  
`$> ./analyse_runs.rb results/complete-le-3-8-12-200ms.txt`

<br>
  
## Analyse result files from Experiment 3
/\* in problems folder \*/  
`$> ./analyse_results.rb xyz/results/2021-10-27/the_file_you_want`

### For instance
/\* to print results about Sudoku 9x9 with learned error function run through the ICN:\*/ 
`$> ./analyse_results.rb results/2021-10-27/3_sudoku_fastforward.txt`

<br>
  
## Compute the test error of a learned error function over its test set
/\* in learn_cp folder \*/  
/\* Compile first the program computing the test error \*/  
`$> ../lear_ga/compilation/compile_get_score.sh`  
`$> ../learn_ga/bin/get_score (and many options, type -h first to have them)`

### For instance
/\* to get the test error of the most frequently learned error function over the LinearSum-3-8-12 complete constraint space:\*/  
`$> ../learn_ga/bin/get_score -c le -n 100 -d 100 -p 5279 -f 10000000000000000001010000000 -hi ../learn_ga/test_sets/true-le-100-5279-10000_h-m.txt`


# Folders:

## root

* learn_cp: current learning via EFOP
* learn_ga: old learning via GA
* constraints: different constraints to study
* tests: handmade test files (not well-defined unit tests)
* utils: get next configuration, random lib, Latin Hypercube Sampling, ...

## problems

* magic_square: Magic Square benchmark
* sudoku: Sudoku benchmarks
* killer_sudoku: Killer Sudoku benchmarks
* vertex_cover: Vertex Cover benchmarks. Work on the small instance, but there is a bug somewhere for the large instance.

## explored

* cfn: searching for error functions through a Error Function Network (so meta)
* cfn_cppn: searching for error functions modeled with a CPPN through a Error Function Network
* chebpol: interpolation
* csv: to make CSV files and interpolate error functions from them
* eigen: Eigen lib
* eo: searching for error functions through genetic algorithms
* JLL: everything related to the Johnson–Lindenstrauss Lemma 

