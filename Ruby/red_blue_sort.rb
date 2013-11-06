class SortInLinearTime
    a = ["r", "b", "r", "r", "b", "r"]

    def swap(a, i, j)
        temp = a[i]
        a[i] = a[j]
        a[j] = temp
    end

    def sort_in_linear_time_and_constant_extra_space a
        i = 0
        j = a.length
        while i<j do
            case a[i]
            when "r"
                i+=1
            when "b"
                if  a[j] == "r"
                    swap(a, i, j)
                    i += 1
                else
                    j -= 1
                end
            end
        end
    end

    sort_in_linear_time = SortInLinearTime.new
    sort_in_linear_time.sort_in_linear_time_and_constant_extra_space(a)
    p a
end
