class Variables

    attr_accessor :b

    @a = 0 #instance variable that belongs to class
    @@b = 1

    def foo
        puts "a: #{@a}" #Instance variable that now belongs to method
        puts "b: #{@@b}" #class variable that was initialized
        puts "c: #{@@c}" #class variable that is initialized when the method bar is called
    end

    def bar
        @@c = 1 #class variable is initialized.
    end

    t = Variables.new
    t.bar #if "bar" is not called before "foo" an exception will be thrown for undefined class variable.
    t.foo

    puts "Attr acc. b: #{t.b}"
    t.b = "hello"
    puts "Attr acc. b: #{t.b}"

    puts "a inside class #{@a}" #a is an instance variable of class and was already defined.
end

