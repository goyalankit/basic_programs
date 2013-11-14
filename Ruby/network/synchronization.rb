require 'monitor'

class Counter
    attr_accessor :count, :tmp

    def initialize
        @count = 0
        @tmp = 0
        super
    end

    def increment
        @count += 1
    end

    def increment_temp 
        @tmp += 1 if @count.even?;
    end
end

c = Counter.new
lock = Monitor.new

t1 = Thread.start do 
    1000000.times do
        lock.synchronize do
            c.increment;
            c.increment_temp
        end
    end
end

t2 = Thread.start do 
    1000000.times do
        lock.synchronize do
            c.increment;
            c.increment_temp
        end
    end
end


t1.join
t2.join

p c.count #200_0000
p c.tmp # not 100_000, different every time
