class SpiralMatrixTraversal

    def initialize n, m, y_start, x_start
        @first  = n
        @second = m
        @y_start  = y_start
        @x_start = x_start
        @matrix = self.create_matrix
    end

    def create_matrix
        @matrix = []
        count = 1
        @first.times do |i|
            inner_vector = []
            @second.times do |j|
                inner_vector << count
                count += 1
            end
            @matrix << inner_vector
        end
        @matrix
    end

    def spiral_matrix_order
        operations = [[-1,0], [0,-1], [1,0], [0,1]]

        apply_operation_ntimes = 1
        y_walker = @y_start - 1
        x_walker = @x_start - 1
        opertaion_number = 0
        spiral_order = []
        spiral_order << @matrix[y_walker][x_walker]
        number_printed = 1

        while(number_printed != (@first * @second))
            apply_operation_ntimes.times do |i|
                op = operations[opertaion_number  % 4]
                y_walker = y_walker + op[0]
                x_walker = x_walker + op[1]
                unless @matrix[y_walker].nil? or @matrix[y_walker][x_walker].nil? or (y_walker < 0) or (x_walker < 0)
                    spiral_order << @matrix[y_walker][x_walker]
                    number_printed += 1
                end
            end

            opertaion_number += 1
            apply_operation_ntimes += 1 if (opertaion_number % 2 == 0)
        end
        spiral_order
    end

    first_example = SpiralMatrixTraversal.new(5, 5, 3, 3)
    p first_example.spiral_matrix_order


    second_example = SpiralMatrixTraversal.new(2, 4, 1, 2)
    p second_example.spiral_matrix_order
end
