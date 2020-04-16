# How to:

## Compile the main program to learn Cost Functions

`$> cd learn`  
`$> ./compile_learn_ga.sh`

<br>
  
## Run the main program to learn Cost Functions
/\* in learn folder \*/  
`$> ./bin/learn_cf_ga (and many options, type -h first to have them)`

### For instance
/\* to learn a cost function for AllDifferent-4-5 over 1000 Latin hypercube samplings:\*/  
`$> ./bin/learn_cf_ga -c ad -n 4 -d 5 -l -s 1000`

<br>
  
## Run the main program to learn Cost Functions using precomputed \*\*incomplete\*\* constraint spaces
/\* in learn folder \*/  
`$> ./bin/learn_cf_ga -i spaces/the_file_you_want (plus many other options, type -h first to have them)`

### For instance
/\* to learn a cost function from the Ordered-6-9 incomplete constraint space with 100 Latin hypercube samplings:\*/  
/\* 'lt' stands for LessThan, the Ordered constraint implementation we choose for this paper.\*/  
`$> ./bin/learn_cf_ga -c lt -n 6 -d 9 -i spaces/lt-6-9-100-la.txt`

<br>
  
## Run the main program to learn Cost Functions using precomputed \*\*complete\*\* constraint spaces
/\* in learn folder \*/  
`$> ./bin/learn_cf_ga -ci spaces/complete_the_file_you_want (plus many other options, type -h first to have them)`

### For instance
/\* to learn a cost function from the LinearSum-3-8-12 complete constraint space:\*/  
/\* 'le' stands for LinearEquation.\*/  
`$> ./bin/learn_cf_ga -c le -n 3 -d 8 -p 12 -ci spaces/complete_le-3-8-12.txt`

<br>
  
## Re-run Experiment 1
/\* in learn folder \*/  
`$> ./run_complete_space_xp.sh (then relax and wait for one hour or so)`

### Warning
This will add new results into result files in the results folder. You need to either change the script or rename the corresponding files.

<br>
  
## Re-run Experiment 2
/\* in learn folder \*/  
`$> ./run_xp.sh (then relax and wait for two weeks or so)`

### Warning
This will add new results into result files in the results folder. You need to either change the script or rename the corresponding files.

<br>
  
## Re-run Experiment 3
/\* in problems/sudoku folder \*/  
/\* Compile the four models first \*/  
`$> ./compile_sudoku_nocfn.sh ; ./compile_sudoku.sh ; ./compile_sudoku_hardcoded.sh ; ./compile_sudoku_handmade.sh`

`$> ./run_sudoku_xp.sh (then relax and wait for 10 minutes or so)`

### Warning
This will add new results into result files in the results folder. You need to either change the script or rename the corresponding files.

<br>
  
## Analyse result files from Experiments 1 and 2 (this will also print the 3 most frequently learned cost functions)
/\* in learn folder \*/  
/\* Compile first the program printing models \*/  
`$> ./compile_print_model.sh`  
`$> ./analyse_runs.sh results/the_file_you_want`

### For instance
/\* to print results about LinearSum-3-8-12 learned upon the complete constraint space:\*/  
`$> ./analyse_runs.sh results/complete/complete-le-3-8-12.txt`

<br>
  
## Analyse result files from Experiment 3
/\* in problems/sudoku folder \*/  
`$> ./analyse_results.rb results/the_file_you_want`

### For instance
/\* to print results about Sudoku with learned cost function run through the neural network:\*/  
`$> ./analyse_results.rb results/sudoku.txt`

<br>
  
## Compute the test error of a learned cost function over its test set
/\* in learn folder \*/  
/\* Compile first the program computing the test error \*/  
`$> ./compile_get_score.sh`  
`$> ./bin/get_score (and many options, type -h first to have them)`

### For instance
/\* to get the test error of the most frequently learned cost function over the LinearSum-3-8-12 complete constraint space:\*/  
`$> ./bin/get_score -c le -n 100 -d 100 -p 5279 -f 10000000000000000001000010000 -hi hamming/true-le-100-5279-10000.txt`

### Warning
This will output the sum of test errors over the 20,000 test configurations. In this example, it should be 758. To get the average test error, you need to divide this by the number of test configurations. Here, 758 / 20,000 is about 0.03


# Folders:

## root

* learn: main folder (ICN learned via GA)
* constraints: different constraints to study
* tests: handmade test files (not well-defined unit tests)
* utils: get next configuration, random lib, Latin Hypercube Sampling, ...

## problems

* magic_square: Magic Square benchmark
* sudoku: Sudoku and Killer Sudoku benchmarks

## explored

* cfn: searching for cost functions through a Cost Function Network (so meta)
* cfn_cppn: searching for cost functions modeled with a CPPN through a Cost Function Network
* chebpol: interpolation
* csv: to make CSV files and interpolate cost functions from them
* eigen: Eigen lib
* eo: searching for cost functions through genetic algorithms
* JLL: everything related to the Johnson–Lindenstrauss Lemma 

