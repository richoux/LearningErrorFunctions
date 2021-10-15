#!/usr/bin/ruby

require 'rubygems'
require 'descriptive-statistics'

def usage
  puts  "Usage: " + $0 + " RESULT_FILE CONSTRAINT_TYPE NB_VAR DOMAIN_SIZE [PARAMETER] HAMMING_FILE"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

results_file = ARGV[0]
constraint_type = ARGV[1]
nb_var = ARGV[2].to_i
domain_size = ARGV[3].to_i

if ARGV.length == 6
  parameter = ARGV[4].to_i
  hamming_file = ARGV[5]
else
  hamming_file = ARGV[4]
end

results = %x[ ./analyse_runs.rb #{results_file} ]
scores = Hash.new(0)
functions = Hash.new
lines = results.split("\n")

most_freq_score = 0
first_loop = true

# For each line in file
lines.each do |line|		
  if line.start_with?("space")
    break
  else
    words = line.split(' ')
    function = words[0]
    occurence = words[1].to_i
    
    if ARGV.length == 6
      get_score = %x[ ./bin/get_score -c #{constraint_type} -n #{nb_var} -d #{domain_size} -p #{parameter} -hi #{hamming_file} -f #{function} ]
    else
      get_score = %x[ ./bin/get_score -c #{constraint_type} -n #{nb_var} -d #{domain_size} -hi #{hamming_file} -f #{function} ]
    end

    score_lines = get_score.split("\n")
    score = 0

    #puts score_lines
    
    score_lines.each do |score_line|
      if score_line.start_with?("Mean error")
        words_score = score_line.split(': ')
        score = words_score[1].to_f
        functions[score] = function
      end
    end

    if first_loop
      most_freq_score = score
      first_loop = false
    end

    scores[score] = scores[score] + occurence
  end
end

score_array = []
puts "Model \t\t\t\t occurence \t score"
functions.each do |score, model|
  puts "#{model} \t #{scores[score]} \t\t #{score}"
  for i in 0..scores[score]
    score_array << ( score / nb_var )
  end
end

sorted_score_array = score_array.sort
stats = DescriptiveStatistics::Stats.new(sorted_score_array)
most_freq = most_freq_score / nb_var
puts "Normalized statistics:"
puts "Most freq: #{most_freq}"
puts "Median: #{stats.median}"
puts "Mean: #{stats.mean}"
puts "Sample standard deviation: #{stats.standard_deviation}"

