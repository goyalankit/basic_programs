class BinaryTree
    attr_accessor :left, :right, :data

    def initialize data
        @data = data
    end

    def self.create_tree
        root = BinaryTree.new(3)
        root.left = BinaryTree.new(9)
        root.left.right = BinaryTree.new(5)
        root.right = BinaryTree.new(20)
        root.right.left = BinaryTree.new(15)
        root.right.right = BinaryTree.new(7)
        root
    end
end

class KaryTree
    attr_accessor :children, :data

    def initialize data
        @data  = data
        @children = []
    end

    def self.create_tree
        root = KaryTree.new(10)
        root.children = [ KaryTree.new(5), KaryTree.new(3), KaryTree.new(1)]
        root.children[0].children = [ KaryTree.new(13), KaryTree.new(15), KaryTree.new(16)]
        root.children[0].children[0].children = [ KaryTree.new(5), KaryTree.new(2), KaryTree.new(0)]
        root
    end
end

class PrintTreeByLevel
    def self.print_binary_tree t
        queue = []
        queue.push(t)
        current_level = 1
        next_level = 0

        while(!queue.empty?) do
            node = queue.shift
            current_level -= 1
            print "#{node.data} "

            unless node.left.nil?
                queue.push(node.left) 
                next_level += 1
            end

            unless node.right.nil?
                queue.push(node.right) 
                next_level += 1
            end

            if(current_level == 0)
                print "\n"
                current_level = next_level
                next_level = 0
            end
        end
    end

    def self.print_kary_tree t
        queue = []
        queue.push(t)
        current_level = 1
        next_level = 0

        while(!queue.empty?) do
            node = queue.shift
            current_level -= 1
            print "#{node.data} "

            node.children.each do |child|
                queue.push(child) 
                next_level += 1
            end

            if(current_level == 0)
                print "\n"
                current_level = next_level
                next_level = 0
            end
        end
    end

    b_t = BinaryTree.create_tree
    #    PrintTreeByLevel.print_binary_tree(b_t)

    k_t = KaryTree.create_tree
    PrintTreeByLevel.print_kary_tree k_t
end
