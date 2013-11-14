#
# Collection of problems solved in one line
# Code may not be optimal with respect to time and/or space complexity
# Just for fun
#
###############################################################################################################################
#PROBLEM 1
# Given two (dictionary) words as Strings, determine if they are isomorphic. Two words are called isomorphic
# if the letters in one word can be remapped to get the second word. Remapping a letter means replacing all
# occurrences of it with another letter while the ordering of the letters remains unchanged. No two letters
# may map to the same letter, but a letter may map to itself.
#
# Example:
# given "foo", "app"; returns true
# we can map 'f' -> 'a' and 'o' -> 'p'
#
# given "bar", "foo"; returns false
# we can't map both 'a' and 'r' to 'o'
#
# given "turtle", "tletur"; returns true
# we can map 't' -> 't', 'u' -> 'l', 'r' -> 'e', 'l' -> 'u', 'e' ->'r'
#
# given "ab", "ca"; returns true
# we can map 'a' -> 'c', 'b' -> 'a'
#y procedure calculates the frequency of each character in the string
y = Proc.new{|x| x.chars.group_by{|i| i}.values.collect{|i| i.count}}
z = Proc.new{|m,n| y.call(m) == y.call(n)}
z.call("foo", "app")


#the one liner, less readable..:) well technically two to make it general
y = Proc.new{|m,n| m.chars.group_by{|i| i}.values.collect{|i| i.count} == n.chars.group_by{|i| i}.values.collect{|i| i.count} }
y.call("foo", "app")


###############################################################################################################################
#PROBLEM 2
#Tell if a String is a Number: Example "-123.3" is a number but "-2.2.3" is not.

y = Proc.new{|x| x.match(/^[+|-]{0,1}(\d)*\.?\d+$/) ? true : false}
y.call("-0.02") #true

###############################################################################################################################
#PROBLEM 3
#Give an array of integers, which are in repeated format except one integer, write a function to return that integer.
#
#For example, [2,2,3,3,4,4,4,5,5] = 4, [2,2,2,3,3,3,3,4,4,4] = 3
#
#CAUTION! Extremely bad code ahead. Wrote just for the sake of it.
a = [2,2,3,3,4,4,4,5,5]
a.inject({}){|hsh,i| hsh[i] = (hsh[i] || 0) + 1;hsh}.group_by{|k,v| v}.map{|k,v| [v,k]}.min{|a,b| a[0].count <=> b[0].count}[0][0][0]


