# =>Refer: http://stackoverflow.com/questions/1872110/is-ruby-pass-by-reference-or-by-value
#
# Ruby pass by value or reference?
#


class Example1
    #In ruby it's always the value that is passed. That value could be the pointer value
    def self.foo(bar)
        #the value passed is the reference but when you reassign a new object is created and variable is assigned it's value
        p "bar object id before assigning: #{bar.object_id}"
        bar = 'reference'
        p "bar object id after assigning: #{bar.object_id}"
    end

    baz = 'value'
    p "baz object id: #{baz.object_id}"

    foo(baz)

    puts "Ruby is pass-by-#{baz}"
    # Ruby is pass-by-value
end

class Example2
    #In ruby it's always the value that is passed. That value could be the pointer value
    def self.foo(bar)
        puts bar
    end

    baz = 'value'

    foo(baz)

    puts "Ruby is pass-by-#{baz}"
    # Ruby is pass-by-value
end
