#Reverse the characters of a string in place
#without constructing a new string.
#Snapstream interview

sample_string = "ruby"

sample_string = gets

(sample_string.length / 2 ).times.each do |i|
    replaced_character = sample_string[0+i]
    sample_string[i] = sample_string[-1-i]
    sample_string[-1-i] = replaced_character
end

puts sample_string
