#!/usr/bin/ruby

require 'rubygems'
require 'descriptive-statistics'

def usage
  puts  "Usage: " + $0 + " COSTS_FILE"
end

def compute_true_score( constraint_type, nb_var, domain_size, param, candidate )
  cost = 0
  if( constraint_type == "ad" )
    for d in 1..domain_size
      candidate.map! { |val| val -= 1 }
      cost += [( candidate.count { |val| val == 0 } ) - 1, 0].max
    end
  else 
    if ( constraint_type == "le" )
      sum = candidate.sum
      while sum != param
        diff = ( sum - param ).abs
        if sum < param
          minimum = candidate.min
          index = candidate.index( minimum )
          if diff <= ( domain_size - minimum )
            candidate[index] += diff
          else
            candidate[index] = domain_size - 1 
          end
        else
          maximum = candidate.max
          index = candidate.index( maximum )
          if diff < maximum
            candidate[index] -= diff
          else
            candidate[index] = 1
          end
        end
        
        cost += 1
        sum = candidate.sum
      end      
    else
      if ( constraint_type == "cm" )
        cost = candidate.count { |val| val < param }
      else
        return -1
      end
    end
  end

  return cost
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

costs_file = ARGV[0]

filename = costs_file.split('/')[-1]
arguments = filename.split('-')

if arguments[0].start_with?("complete")
  constraint_type = arguments[0].split('_')[1]
  if arguments.length >= 4
    param = arguments[3].split('_')[0].to_i
  else
    param = 0
  end
else
  constraint_type = arguments[0]
  if arguments.length >= 5
    param = arguments[4].to_i
  else
    param = 0
  end
end

nb_var = arguments[1].to_i
domain_size = arguments[2].to_i

scores_diff = Array.new

file = File.open( costs_file )

# For each line in file
file.each do |line|		
  candidate = Array.new
  words = line.split(' ')
  estimated_score = words[1].to_i
  if( estimated_score != 0 )
    assignments = words[0].split('_')
    assignments.each do |value|
      candidate.push( value.to_i )
    end
    #puts "#{candidate}"
    true_score = compute_true_score( constraint_type, nb_var, domain_size, param, candidate )
    if true_score == -1
      puts "Error: constraint type is invalid"
      exit 1
    end
    #puts "#{estimated_score} - #{true_score}"
    #puts ""
    
    scores_diff.push( ( estimated_score - true_score ).abs )
  end 
end

file.close

scores_diff.sort!
stats = DescriptiveStatistics::Stats.new(scores_diff)
puts "Global: #{scores_diff.sum}"
puts "Median: #{stats.median}"
puts "Mean: #{stats.mean}"
puts "Sample standard deviation: #{stats.standard_deviation.round(4)}"
