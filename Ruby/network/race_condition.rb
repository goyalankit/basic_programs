class Counter
    attr_accessor :count, :tmp

    def initialize
        @count = 0
        @tmp = 0
    end

    def increment
        @count += 1
    end
end

c = Counter.new

#due to ruby's Global interpreter lock you will not get a  race condition if there's only one statement
#in this case there are two statements and it may happen that one of the statements ran and then the context switch happened.
#this could cause race condition. 
#Check synchronization.rb to see how to fix this issue
t1 = Thread.start { 1000000.times { c.increment; c.tmp += 1 if c.count.even?; } }
t2 = Thread.start { 1000000.times { c.increment; c.tmp += 1 if c.count.even?; } }

t1.join
t2.join

p c.count #200_0000
p c.tmp # not 100_000, different every time
