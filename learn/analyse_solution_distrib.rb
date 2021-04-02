#!/usr/bin/ruby

require 'rubygems'
require 'descriptive-statistics'

def usage
  puts  "Usage: " + $0 + " SPACE_FILE [SAMPLES (100 by default)] [NB SOLUTIONS IN MILLION]"
end

def binomial(n,k)
  (1+n-k..n).inject(:*)/(1..k).inject(:*)
end

if ARGV.length < 1 || ARGV.length > 3
  usage
  exit
end

filename = ( ARGV[0] ).split('/')[-1]
arguments = filename.split('-')

nb_var = arguments[1].to_i
domain_size = arguments[2].delete('.txt').to_i
space_size = domain_size ** nb_var

file = File.open( ARGV[0] )
if ARGV.length == 1
  samples = 100
else
  samples = ARGV[1].to_i
end

total_number_solutions = 0
if ARGV.length == 3
  total_number_solutions = ARGV[2].to_i * 1000000
end

solutions = Array.new
distribution = Hash.new( 0 )

number_line = 0
counter = 0
assignments = []

# For each line in file
file.each do |line|
  if arguments[0].start_with?("complete")
    if line.start_with?("1")
      words = line.split(' : ')
      assignments = words[1].delete("\n").split(' ')
      solution = Array.new
      assignments.each do |val|
        solution.push( val.to_i )
      end
      solutions.push( solution )
    end
  else
    if number_line == 0
      number_line = line.to_i
    else
      if counter < number_line
        assignments = line.delete("\n").split(' ')
        counter += 1
        solution = Array.new
        assignments.each do |val|
          solution.push( val.to_i )
        end
        solutions.push( solution )
      else
        break
      end
    end
  end
end
file.close

if samples > solutions.size
  samples = solutions.size
end

solutions.shuffle!

for c in 0...samples
  current = solutions[c]
  solutions.each do |solution|
    if( current != solution )
      count = 0
      for i in 0...current.length
        if( current[i] != solution[i] )
          count += 1
        end
      end
      distribution[count] += 1
    end
  end
end

distrib_mean = Hash.new(0.0)
if total_number_solutions != 0
  distribution.each do |key, value|
    distrib_mean[key] = ( value.to_f * total_number_solutions / ( samples**2 ) ).round(4)
  end
else
  distribution.each do |key, value|
    distrib_mean[key] = ( value.to_f / samples ).round(4)
  end
end

sorted_distrib_mean = distrib_mean.sort
stats_distrib = DescriptiveStatistics::Stats.new(sorted_distrib_mean.to_h.values)

ratios = Hash.new
distrib_mean.each do |key, value|
  ratios[key] = ( value / ( (domain_size ** key) * binomial( nb_var, key ) - (key*nb_var) ) ).round(4)
end

sorted_ratios = ratios.sort
stats_ratios = DescriptiveStatistics::Stats.new(sorted_ratios.to_h.values)

puts "Search space size: #{space_size}"
puts "Number of solutions: #{solutions.size}"
puts "Samples: #{samples}"
puts "Distribution: #{distrib_mean.sort.to_h}"
puts "Sample standard deviation: #{stats_distrib.standard_deviation.round(4)}"
puts "Ratios: #{sorted_ratios.to_h}"
puts "Sample standard deviation: #{stats_ratios.standard_deviation.round(4)}"
