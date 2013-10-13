#
#Author: Ankit Goyal
#Date: 10/12/2013
#
#Simple binary tree implementation with basic traversal methods
#
#Sample Tree:
#
#            10
#        15      16
#     13    19
#
# Inorder: 13 15 19 10 16
# Preorder: 10 15 12 19 16
# Postorder: 13 19 15 16 10
# Number of nodes: 5

class Tree
  attr_accessor :value, :left, :right

  def initialize(v)
    @value = v
  end

  class << self
    def inOrder root
      unless root.nil?
        inOrder root.left
        print "#{root.value} "
        inOrder root.right
      end
    end

    def preOrder root
      unless root.nil?
        print "#{root.value} "
        preOrder root.left
        preOrder root.right
      end
    end

    def postOrder root
      unless root.nil?
        postOrder root.left
        postOrder root.right
        print "#{root.value} "
      end
    end

    def countNodes root
      count = 0
      unless root.nil?
        count += 1
        count += countNodes root.left
        count += countNodes root.right
      end
      count
    end
  end
end

root = Tree.new(10)
n1 = Tree.new(15)
root.left = n1
n1.left = Tree.new(13)
n2 = Tree.new(19)
n1.right = n2
root.right = Tree.new(16)

print "Inorder: "
Tree.inOrder root
print "\nPreorder: "
Tree.preOrder root
print "\nPostOrder: "
Tree.postOrder root
print "\nNumber of nodes: #{Tree.countNodes root}\n"
