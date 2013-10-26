first  = 2
second = 4
y_start  = 1
x_start = 2

matrix = []
count = 1

first.times do |i|
    inner_vector = []
    second.times do |j|
        inner_vector << count
        count += 1
    end
    matrix << inner_vector
end

p "the input matrix is #{matrix}"

operations = [[-1,0], [0,-1], [1,0], [0,1]]

apply_operation_ntimes = 1

y_walker = y_start - 1
x_walker = x_start - 1
opertaion_number = 0

print "#{matrix[y_walker][x_walker]} "
number_printed = 1

while(number_printed != (first * second))

    apply_operation_ntimes.times do |i|
        op = operations[opertaion_number  % 4]
        y_walker = y_walker + op[0]
        x_walker = x_walker + op[1]
        unless matrix[y_walker].nil? or (y_walker < 0) or (x_walker < 0)
            print "#{matrix[y_walker][x_walker]} " unless matrix[y_walker][x_walker].nil?
            number_printed += 1 unless matrix[y_walker][x_walker].nil?
        end

    end

    opertaion_number += 1
    apply_operation_ntimes += 1 if (opertaion_number % 2 == 0)
end
