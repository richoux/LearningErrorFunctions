## How to:

1. Compile the main program to learn Cost Functions.\
$> cd learn\
$> ./compile_learn_ga.sh

2. Run the main program to learn Cost Functions.\
$> (in learn folder)\
$> ./bin/learn_cf_ga (and many options, type -h first to have them)

3. Run the main program to learn Cost Functions using precomputed **incomplete** constraint spaces.\
$> (in learn folder)\
$> ./bin/learn_cf_ga -i spaces/the_file_you_want (plus many other options, type -h first to have them)

4. Run the main program to learn Cost Functions using precomputed **complete** constraint spaces.\
$> (in learn folder)\
$> ./bin/learn_cf_ga -ci spaces/complete_the_file_you_want (plus many other options, type -h first to have them)

5. Re-run Experiment 1\
$> (in learn folder)\
$> ./run_complete_space_xp.sh (then relax and wait for one hour or so)

6. Re-run Experiment 2\
$> (in learn folder)\
$> ./run_xp.sh (then relax and wait for two weeks or so)

7. Re-run Experiment 3\
$> (in problems/sudoku folder)\
/* Compile the three models first */\
$> ./compile_sudoku_nocfn.sh ; ./compile_sudoku.sh ; ./compile_sudoku_handmade.sh\
$> ./run_sudoku_xp.sh (then relax and wait for 10 minutes or so)

8. Analyse result files from Experiments 1 and 2\
$> (in learn folder)\
$> ./analyse_runs.sh results/the_file_you_want

9. Analyse result files from Experiment 3\
$> (in problems/sudoku folder)\
$> ./analyse_results.rb results/the_file_you_want



## Folders:

### root

* learn: main folder (CPPN learned via GA)
* constraints: different constraints to study
* tests: handmade test files (not well-defined unit tests)
* utils: get next configuration, random lib, Latin Hypercube Sampling, ...

### problems

* magic_square: Magic Square benchmark
* sudoku: Sudoku and Killer Sudoku benchmarks

### explored

* cfn: searching for cost functions through a Cost Function Network (so meta)
* cfn_cppn: searching for cost functions modeled with a CPPN through a Cost Function Network
* chebpol: interpolation
* csv: to make CSV files and interpolate cost functions from them
* eigen: Eigen lib
* eo: searching for cost functions through genetic algorithms
* JLL: everything related to the Johnson–Lindenstrauss Lemma 

