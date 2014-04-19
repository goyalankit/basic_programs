#!/bin/ruby

=begin
Problem

Recently you went to a magic show. You were very impressed by one of the tricks, so you decided to try to figure out the secret behind it!

The magician starts by arranging 16 cards in a square grid: 4 rows of cards, with 4 cards in each row. Each card has a different number from 1 to 16 written on the side that is showing. Next, the magician asks a volunteer to choose a card, and to tell him which row that card is in.

Finally, the magician arranges the 16 cards in a square grid again, possibly in a different order. Once again, he asks the volunteer which row her card is in. With only the answers to these two questions, the magician then correctly determines which card the volunteer chose. Amazing, right?

You decide to write a program to help you understand the magician's technique. The program will be given the two arrangements of the cards, and the volunteer's answers to the two questions: the row number of the selected card in the first arrangement, and the row number of the selected card in the second arrangement. The rows are numbered 1 to 4 from top to bottom.

Your program should determine which card the volunteer chose; or if there is more than one card the volunteer might have chosen (the magician did a bad job); or if there's no card consistent with the volunteer's answers (the volunteer cheated).

Solving this problem

Usually, Google Code Jam problems have 1 Small input and 1 Large input. This problem has only 1 Small input. Once you have solved the Small input, you have finished solving this problem.

Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a line containing an integer: the answer to the first question. The next 4 lines represent the first arrangement of the cards: each contains 4 integers, separated by a single space. The next line contains the answer to the second question, and the following four lines contain the second arrangement in the same format.

Output

For each test case, output one line containing "Case #x: y", where x is the test case number (starting from 1).

If there is a single card the volunteer could have chosen, y should be the number on the card. If there are multiple cards the volunteer could have chosen, y should be "Bad magician!", without the quotes. If there are no cards consistent with the volunteer's answers, y should be "Volunteer cheated!", without the quotes. The text needs to be exactly right, so consider copying/pasting it from here.

Limits

1 ≤ T ≤ 100.
1 ≤ both answers ≤ 4.
Each number from 1 to 16 will appear exactly once in each arrangement.
=end


require 'pry'

test_case = {
    :ans1 => 0,
    :ans2 => 0,
    :arrangement1 => [],
    :arrangement2 => []
}

inputs = {}

contents = File.read("magic.in")

ia = contents.split("\n")

num_inputs = ia[0].to_i

counter = 1

num_inputs.to_i.times do |i|
    inputs[i] = {}
    inputs[i][:ans1] = ia[counter+0]
    inputs[i][:arrangement1] = ia[(counter+1)..(counter+4)].map{|j| j.split(" ")}
    inputs[i][:ans2] = ia[counter+5]
    inputs[i][:arrangement2] = ia[(counter+6)..(counter+10)].map{|j| j.split(" ")}
    counter = counter + 10
end

num_inputs.to_i.times do |ip|
    ds = inputs[ip]
    possible1 = ds[:arrangement1][ds[:ans1].to_i-1]
    possible2 = ds[:arrangement2][ds[:ans2].to_i-1]
    guess = possible2 & possible1

    if guess.count == 1
        puts "Case ##{ip+1}: #{guess[0]}"
    elsif guess.count > 1
        puts "Case ##{ip+1}: Bad magician!"
    else
        puts "Case ##{ip+1}: Volunteer cheated!"
    end
end
