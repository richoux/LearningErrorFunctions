#!/usr/bin/ruby

def usage
  puts  "Usage: " + $0 + " FILE"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

file = File.open(ARGV[0])

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
      time += get_rid_of_ms[0].to_f
    end
  end
end

if not success == 100
  puts "Warning: we do not have 100 solutions.\n"
  exit
end

mean = ( time.to_f / 100 ).round(2)                

puts "Mean time: #{mean}ms\n"

exit
