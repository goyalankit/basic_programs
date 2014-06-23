"""
Write a program that prints the numbers from 1 to 100.
But for multiples of three print "Fizz" instead of the number and for the multiples of five print "Buzz".
For numbers which are multiples of both three and five print "FizzBuzz".
"""

def fizz_buzz():
    for n in range(101):
        str = ''
        if n % 3 == 0:
            str += 'Fizz'
        if n % 5 == 0:
            str += 'Buzz'
        print str or n

fizz_buzz()
