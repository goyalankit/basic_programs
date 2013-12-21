from sys import argv
#python has more control over global namespace

#----------------------------------------
# BASIC UNPACKING OF ARGUMENTS
#

#script, first, second, third = argv

#print "The script is called:", script
#print "Your first variable is:", first
#print "Your second variable is:", second
#print "Your Third variable is:", third

#------------------------------------------


script, user_name = argv

prompt = "> "

print "Hi! %s, I am the %s script" % (user_name, script)
print "I'd like to ask few questions"
print "Do you like me %s" % user_name
likes = raw_input(prompt)

print "Where do you live %s" % user_name
lives = raw_input(prompt)
