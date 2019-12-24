How to:

1. Compile the main program to learn Cost Functions.
$> cd learn
$> ./compile_learn_ga.sh

2. Run the main program to learn Cost Functions.
$> (in learn folder)
$> ./bin/learn_cf_ga (and many options, type -h first to have them)

3. Run the main program to learn Cost Functions using precomputed constraint spaces.
$> (in learn folder)
$> ./bin/learn_cf_ga -i spaces/the_file_you_want (plus many other options, type -h first to have them)

4. Re-run our experiments
$> (in learn folder)
$> ./run_xp.sh (then relax and wait for a week or so)

5. Analyse result files
$> (in learn folder)
$> ./analyse_runs.sh results/the_file_you_want



Folders:

\\\\\\\\\\
\\ root \\
\\\\\\\\\\

learn: main folder (CPPN learned via GA)
constraints: different constraints to study
tests: handmade test files (not well-defined unit tests)
utils: get next configuration, random lib, Latin Hypercube Sampling, ...


\\\\\\\\\\\\\\
\\ problems \\
\\\\\\\\\\\\\\

magic_square: Magic Square benchmark
sudoku: Sudoku and Killer Sudoku benchmarks


\\\\\\\\\\\\\\
\\ explored \\
\\\\\\\\\\\\\\

cfn: searching for cost functions through a Cost Function Network (so meta)
cfn_cppn: searching for cost functions modeled with a CPPN through a Cost Function Network
chebpol: interpolation
csv: to make CSV files and interpolate cost functions from them
eigen: Eigen lib
eo: searching for cost functions through genetic algorithms
JLL: everything related to the Johnson–Lindenstrauss Lemma 

