require 'rubygems'
require 'pry'

class Object
  attr_accessor :affirmative

  def should= obj
    if ((self == obj) == self.affirmative)
      return true
    else
      raise  "Not Equal"
    end
  end

  def should
    self
  end

  def should_not
    not self
  end

  #def == obj
    #if ((self == obj) == self.affirmative)
      #return true
    #else
      #raise  "Not Equal"
    #end
  #end
end

#class Fixnum
  #def == obj
    #if (self == obj) == self.affirmative
      #return true
    #else
      #raise  "Not Equal"
    #end
  #end
#end


def it str
  begin
    a = yield
  rescue Exception => e
    puts "test failed #{e}"
  end

  if a
    puts "Passed: #{str}"
  else
    puts "Failed: test description \"#{str}\""
  end
end

it "should not be equal" do
  1.should_not == 2
end

puts 1.should_not == 2

#def hputs
  #return unless block_given?
  #a = yield
  #return unless a.is_a?(Hash)
  #a.map {|k,v| puts "#{k}=>#{v}"}
#end
