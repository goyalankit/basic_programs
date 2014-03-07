require 'set'
##
# &&= set only if it is not false.
##
something = "hello"
something &&= "nice"
puts something #nice

##
# To print on stderr. Insted of using $stderr.puts.
##
warn "This is to print on stderr"


##
# If an action can be performed on an array
##
not_array = "hello"

#OR

[*not_array].each { |a| puts a }

##
#  delegate the message
##

at_exit { puts "good bye"  }

myset = Set.new [1, 2]
myset.add(2)
myset.add(3)
puts myset.inspect

##
# Retrieving multiple values from hash
##
myhash = { a: 1, b:2 }
a, b = myhash.values_at(:a, :b)
puts a, b

##
# Get content from regex
##
a = "this is 123 cool"[/\d+/]
b = "this is =really= nice"[/=(.*)=/, 1] #get the cached expression.
puts a, b

puts a
