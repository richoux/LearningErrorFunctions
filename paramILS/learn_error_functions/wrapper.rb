#!/usr/bin/ruby

# if we are using an older version of Ruby than 2.1 
unless [].respond_to? :to_h
  class Array
    def to_h
      Hash[self]
    end
  end
end

# parse all parameters
instance = ARGV[0]
runtime = ARGV[2].to_f
seed = ARGV[4].to_i
params = ARGV[5..-1].each_slice(2).map {|k,v| [k[1..-1], v]}.to_h

cmd = "../../learn/bin/learn_cf_ga --paramILS"

if params.key?("tournament")
  cmd += " --tournament #{params['tournament']}"
end

if params.key?("pop")
  cmd += " --pop #{params['pop']}"
end

if params.key?("steady")
  cmd += " --steady #{params['steady']}"
end

if params.key?("mingen")
  cmd += " --mingen #{params['mingen']}"
end

if params.key?("crossover")
  cmd += " --crossover #{params['crossover']}"
end

if params.key?("mutation")
  cmd += " --mutation #{params['mutation']}"
end

if params.key?("replacement")
  cmd += " --replacement #{params['replacement']}"
end

if params.key?("seed")
  cmd += " --seed #{params['seed']}"
end

instance_param = instance.split('-')

if instance.include?("complete_ol")
  cmd += " -c ol -n #{instance_param[1]} -d #{instance_param[2]} -p #{instance_param[3]}"[0...-4]
end

if instance.include?("complete_lt")
  cmd += " -c lt -n #{instance_param[1]} -d #{instance_param[2]}"[0...-4]
end

if instance.include?("complete_le")
  cmd += " -c le -n #{instance_param[1]} -d #{instance_param[2]} -p #{instance_param[3]}"[0...-4]
end

if instance.include?("complete_ad")
  cmd += " -c ad -n #{instance_param[1]} -d #{instance_param[2]}"[0...-4]
end

if instance.include?("complete_cm")
  cmd += " -c cm -n #{instance_param[1]} -d #{instance_param[2]} -p #{instance_param[3]}"[0...-4]
end

cmd += " -ci #{instance}"

puts(cmd)

# # execute cmd and returns the list of lines for the output
output = `#{cmd}`.split("\n")

quality = $1.to_f if output.any? {|line| line =~ /final quality is (.*)/}
time = $1.to_i if output.any? {|line| line =~ /runtime is (.*)/}
used_seed = $1.to_i if output.any? {|line| line =~ /seed is (.*)/}

if output.include?("SUCCESS")
  status = 'SUCCESS'
else
  status = 'CRASHED'
end

# print final result
puts 'Result: %s, %d, %f, %d'%[status, time, quality, used_seed]
