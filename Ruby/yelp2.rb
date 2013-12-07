class Place
  attr_accessor :tips, :name
  
  def initialize name 
    @name = name
    @tip = []
  end
  
  def add_document tip
    @tip = tip.strip
  end 
end

class MiniSearchEngine
  attr_accessor :name_tip, :tip_index
  
  def initialize
    @name_tip = {}
    @tip_index = {}
  end
  
  def add_document name, tip
    @name_tip[name] = tip    
    tip.split.map{|i| @tip_index[i].nil? ? @tip_index[i] = [name] : @tip_index[i] << name }
  end
  
  def search input
    result = []
    input_tokens = input.split
    input_tokens.each do |token|
      result << @name_tip.select{|k,v| v.match(/#{token}/)}.map{|i| i[0]}
    end
    result
  end
  
  def fast_search input
    result = []
    input_tokens = input.split
    input_tokens.each do |token|
      result << @tip_index[token]
    end
    result.compact
  end
  
  # datastore
  
  #p.add_document("big tasty sandwiches")
  
  
  #places = []
end

# Example



# instantiate an object m 
# m.add_document("/biz/ralphs", "big tasty sandwiches")
# m.add_document("/biz/eatery", "tasty soup")
# m.search("tasty food") -> ["/biz/ralphs", "/biz/eatery"]
# m.search("soup") -> ["/biz/eatery"]

m = MiniSearchEngine.new()
m.add_document("/biz/ralphs", "big tasty sandwiches")
m.add_document("/biz/eatery", "tasty soup")
puts "#### search for 'tasty food' ####"
puts m.search("tasty food")
puts "#### FAST search for 'tasty food' ####"
puts m.fast_search("tasty food")
puts "#### search for 'soup' ####"
puts m.search("soup")
puts "#### FAST search for 'soup' ####"
puts m.fast_search("soup")
