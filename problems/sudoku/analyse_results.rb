#!/usr/bin/ruby

def usage
  puts  "Usage: " + $0 + " FILE"
end

def median(array)
  sorted = array.sort
  len = sorted.length
  (sorted[(len - 1) / 2] + sorted[len / 2]) / 2.0
end

def pop_standard_deviation(array)
  m = array.sum(0.0) / array.length
  sum = array.inject(0){|accum, i| accum +(i-m)**2 }
  Math.sqrt( sum/array.length.to_f )
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

file = File.open(ARGV[0])

times = []
time = 0
success = 0

# For each line in file
file.each do |line|
  words = line.split(':')
  if not words[0] == nil
    if words[0].include? "Satisfaction cost"
      if words[1].to_f == 0
        success += 1
      end
    elsif words[0].include? "Elapsed time"
      get_rid_of_ms = words[1].split('ms')
      runtime = get_rid_of_ms[0].to_f
      time += runtime
      times.push( runtime )
    end
  end
end

if not success == 100
  puts "Warning: we do not have 100 solutions.\n"
  exit
end

mean = ( times.sum(0.0) / times.length ).round(2)                

puts "Mean time: #{mean}ms\n"
puts "Median time: #{median(times).round(2)}ms\n"
puts "Min time: #{times.min.round(2)}ms\n"
puts "Max time: #{times.max.round(2)}ms\n"
puts "Std dev: #{pop_standard_deviation(times).round(2)}ms\n"

exit
