a = [1, 2, 5, 3, 10, 7, 5, 8, 0]

a = [0, 1, 2, 3, 5, 5, 7, 8, 10]
k = 10

hash = {}
a.map{|i| hash[i] = true} #O(n)

final = []

a.each do |n|
    next if k-n == n
    if(hash[k-n])
        print "(#{k-n},#{n})" unless k-n < n
    end
end

print final.uniq
