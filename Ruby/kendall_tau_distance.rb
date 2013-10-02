#
# Run: ruby kendall_tau_distance.rb <filename1> <filename2>
# Given two files with values sorted according to their rank. Calcultae the KendallTau distance.
# This program considers all possible permuations of the given set, not scalable for a large set.
#
#
#

if ARGV.length < 2
  p "please provide two files sorted based on rank values"
  p "Usage: ruby kendall_tau_distance.rb <filename1> <filename2> "
  exit
end


first_rank_list = {}
second_rank_list = {}

count = 0
 File.open(ARGV[0], 'r').each_line do |line|
   count+=1
   first_rank_list[line.strip.to_i] = count
 end

 count = 0
 File.open(ARGV[1], 'r').each_line do |line|
   count+=1
   second_rank_list[line.strip.to_i] = count
 end

all_keys = first_rank_list.keys

possible_sets = []

(0...all_keys.length).each do |i|
  (i...all_keys.length).each do |j|
    possible_sets << [all_keys[i], all_keys[j]] unless i==j
  end
end

distance = 0

possible_sets.each do |k,v|
   distance+=1 if (first_rank_list[k] < first_rank_list[v] and second_rank_list[k] > second_rank_list[v])
end

p distance
