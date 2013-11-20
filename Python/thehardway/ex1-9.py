#
# Learning python the hard way. 
# Just printing stuff here
#

print "hello world"
print "had to write it!"

#just starting out!

print "this is a good thing. I can add 2+2 and get", 2+2, 3>4, 4.0/5

my_first_variable = 2

print "the value of my first variable is", my_first_variable, ". I am not shy to type it out."
#Notice that python adds a space after the ',' concat
print "a","b" #a b

#I can use formatters also
name = "Ankit"
print "hello this is %s. nice to meet you" % name

age = 23
print "I am %s and my age is %d" % (name, age)

#okay you can do some crazy stuff
x = "there are %r kind of people. " % 10
binary = "binary"
do_not = "do not"
y = "those who understand %s and those who %s" % (binary, do_not)

print x
print y

hilarious = False
joke_evaluation = "was the joke funny to you? %r"

print joke_evaluation % hilarious

left_side = "left side of a string"
right_side = " with a right side"

#will not add an extra space here
print left_side + right_side

#Excercise 7
print "Marry had a little lamb."
print "."*10

end1 = "h"
end2 = "e"
end3 = "l"
end4 = "l"
end5 = "o"
end6 = "d"
end7 = "u"
end8 = "d"
end9 = "e"

print end1 + end2 + end3 + end4 + end5, #this , has got some power
print end6 + end7 + end8 + end9

#wooh! more printing
formatter = "%r %r %r %r"
print formatter % (1,2,3,4)
print formatter % (formatter, formatter, formatter, formatter)
#each string is printed with single quotes.
print formatter % ( "I had this thing.", "That you could type up right.", "But it didn't sing.", "So I said goodnight.")

days = "mon\ntue\nwed"
print "some days %s" % days #try %r here. it will give you the "raw value"

print """
Here is something interesting
you can write multiple lines
"""

print """I can use it to escape "" and ' """
