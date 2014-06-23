#!/bin/python


#
# Fibonacci series generator
#

class Fib:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def fibonacci(self):
        while(True):
            yield(self.b)
            self.a, self.b = self.b, self.a + self.b

f = Fib(0,1)

for i in f.fibonacci():
    if i > 100: break
    print(i)

options = { }
