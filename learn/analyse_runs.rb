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
costs = Hash.new(0)
solutions = Hash.new(0)

# Open file
filename = ARGV[0]
file = File.open(filename)

# For each line in file
file.each do |line|		
  words = line.split(' ')
  costs[words[0]] = costs[words[0]] + 1
  sum = sum + words[0].to_f
  beginning_sol = words[2][0..17]
  nb_ones = beginning_sol.count "1"
  if nb_ones == 1
    to_consider = words[2][0..17] + "0" + words[2][19..-1]
  else
    to_consider = words[2]
  end

  # puts "original:    #{words[2]}"
  # puts "transformed: #{to_consider}"
  
  solutions[to_consider] = solutions[to_consider] + 1
end

sorted_costs = costs.sort_by{|k, v| v}.reverse
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

if arguments[0].start_with?("complete")
  nb_var = arguments[2].to_i
  domain_size = (arguments[3].split('_'))[0].to_i
  space_size = domain_size ** nb_var
else
  space_size = 2 * ((arguments[3].split('_'))[0].to_i)
end

puts "space_size = #{space_size}"


# puts "costs: #{costs}"
# puts "sorted costs: #{sorted_costs}"

stats = DescriptiveStatistics::Stats.new(sorted_costs_array)
puts "Median: #{stats.median}"
puts "Mean: #{stats.mean}"
puts "Sample standard deviation: #{stats.standard_deviation}"

# if sorted_costs.length.odd?
#   median = sorted_costs[sorted_costs.length / 2]
# else
#   median = ( sorted_costs[sorted_costs.length / 2 - 1] + sorted_costs[sorted_costs.length / 2] ) / 2
# end
# puts "Median: #{median}"

# mean = sorted_costs.sum(0.0) / sorted_costs.length
# puts "Mean: #{mean}"

# difference = 0
# sorted_costs.each do |cost|
#   difference = difference + (mean - cost)**2
# end
# std_dev = Math.sqrt( difference / ( sorted_costs.length - 1) )
# puts "Sample standard deviation: #{std_dev}"
  
most_found_cost = sorted_costs[0][0]
most_found_model = sorted_solutions[0][0]

puts "\n//////////\nCost of the most commun cost function #{most_found_model}: #{most_found_cost}\nModel of the most commun cost function #{most_found_model}:\n\n"
puts %x[ ./bin/print_model #{most_found_model} ]
