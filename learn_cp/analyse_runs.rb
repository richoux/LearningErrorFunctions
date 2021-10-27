#!/usr/bin/ruby

require 'rubygems'
require 'descriptive-statistics'

def usage
  puts  "Usage: " + $0 + " FILE [ LIMIT ]"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

sum = 0
success = 0
count = 0
costs = Hash.new(0)
solutions = Hash.new(0)
cost_solutions = Hash.new(0)

# Open file
filename = ARGV[0]
file = File.open(filename)

# For each line in file
file.each do |line|		
  words = line.split(' ')
  count = count + 1
  success = success + words[0].to_i
  costs[words[1]] = costs[words[1]] + 1
  sum = sum + words[1].to_f
  beginning_sol = words[2][0..17]
  nb_ones = beginning_sol.count "1"
  if nb_ones == 1
    to_consider = words[2][0..17] + "0" + words[2][19..-1]
  else
    to_consider = words[2]
  end
  
  solutions[to_consider] = solutions[to_consider] + 1
  cost_solutions[to_consider] = words[1]
end

sorted_solutions = solutions.sort_by{|k, v| v}.reverse

sorted_solutions.each do |model, number|
  puts "#{model} #{number}"
end

costs_array = Array.new
costs.each do |cost, number|
  for i in 1..number
    costs_array.push( cost.to_f )
  end
end
sorted_costs_array = costs_array.sort

filename = filename.split('/')[-1]

arguments = filename.split('-')
nb_var = 0

if arguments[0].start_with?("complete")
  nb_var = arguments[1].to_i
  domain_size = arguments[2].to_i
  space_size = domain_size ** nb_var
else
  nb_var = arguments[1].to_i
  space_size = 2 * arguments[3].to_i
end

success_rate = success.to_f * 100 / count;

puts "space_size = #{space_size}"

stats = DescriptiveStatistics::Stats.new(sorted_costs_array)
puts "Success rate: #{success_rate}"
puts "Median: #{stats.median}"
puts "Mean: #{stats.mean}"
puts "Sample standard deviation: #{stats.standard_deviation}"

# Since Hamming/Manhattan fitness (2021-10), outputed scores are already normalized
# normalized_sorted_costs_array = sorted_costs_array.map{ |s| s/nb_var }
# normalized_stats = DescriptiveStatistics::Stats.new(normalized_sorted_costs_array)
# puts "Normalized median: #{normalized_stats.median}"
# puts "Normalized mean: #{normalized_stats.mean}"
# puts "Normalized sample standard deviation: #{normalized_stats.standard_deviation}"

most_found_model = sorted_solutions[0][0]
most_found_cost = cost_solutions[most_found_model].to_f
most_found_cost_normalized = most_found_cost / nb_var
  
puts "\n//////////\nCost of the most commun cost function #{most_found_model}: #{most_found_cost} (norm. #{most_found_cost_normalized})\nModel of the most commun cost function #{most_found_model}:\n\n"
puts %x[ ../learn_ga/bin/print_model #{most_found_model} ]
