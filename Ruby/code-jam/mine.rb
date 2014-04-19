#!/bin/ruby

require 'pry'

inputs = {}

contents = File.read("mine.in")

ia = contents.split("\n")

num_inputs = ia[0].to_i

num_inputs.to_i.times do |i|
    inputs[i] = {}
    ds = ia[i+1].split(" ")
    inputs[i][:R] = ds[0].to_i
    inputs[i][:C] = ds[1].to_i
    inputs[i][:M] = ds[2].to_i
end


input = inputs[0]
def create_matrix r, c
    @matrix = []
    count = 1
    r.times do |i|
        inner_vector = []
        c.times do |j|
            inner_vector << "."
            count += 1
        end
        @matrix << inner_vector
    end
    @matrix
end


def print_matrix matrix, r, c
    r.times do |i|
        c.times do |j|
            print matrix[i][j]
        end
        puts ""
    end
end

def find_next_coordinates cur_r, cur_c, r, c, depth, direction
    if cur_r < r-1-depth && direction == :down
        return cur_r+1, cur_c
    elsif cur_r > depth && direction == :up
        return cur_r-1, cur_c
    elsif cur_c < c-1-depth  && direction == :right
        return cur_r, cur_c+1
    elsif cur_c > depth && direction == :left
        return cur_r, cur_c-1
    end
end

def get_direction cur_r, cur_c, r, c, depth, direction
    if direction.nil?
        return [:down, depth] if r > (cur_r+2)
        return [:left, depth]
    end
    if cur_r == r-1-depth && direction == :down
        return [:right, depth]
    elsif cur_r == depth && direction == :up
        return [:left, depth]
    elsif cur_c == c-1-depth && direction == :right
        return [:up, depth]
    elsif cur_c == depth+1 &&  direction == :left
        return [:down, depth+1]
    else
        return [direction, depth]
    end
end

#p create_matrix 10, 10

num_inputs.times do |ind|
    input = inputs[ind]
    @r = input[:R]
    @c = input[:C]
    @m = input[:M]

    matrix = create_matrix @r, @c

    puts "Case ##{ind+1}:"

    if @m == 0
        matrix[0][0] = "c"
        print_matrix matrix, @r, @c
        next
    end

    matrix[0][0] = "*"
    if @r > 1 && @c > 1
        dirty = 3
    else
       dirty = 1
    end
    placed = 1
    current_row = 0
    current_col = 0
    depth = 0

    clean = @r * @c - (dirty + placed)
    #trivial case
    if clean <= 0
        puts "Impossible"
        next
    end
    @direction = nil
    while placed != @m do
        old_direction = @direction
        @direction, depth = get_direction current_row, current_col, @r, @c, depth, @direction
        current_row, current_col = find_next_coordinates current_row, current_col, @r, @c, depth, @direction
        matrix[current_row][current_col] = "*"

        placed += 1
    end

    m = Proc.new { |a| count = 0; a.map { |i| count += (i=="." ? 1 : 0 ) }; count }
    count_ = matrix.inject(0){|count,i| count+=m.call(i); count}

    if(count_ > 8)
        matrix[@r/2-1][@c/2] = "c"
        print_matrix matrix, @r, @c
    else
        puts "Impossible"
    end
end
