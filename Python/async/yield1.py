def grep(pattern):
    print ("Looking for ", pattern)
    while True:
        line = (yield)
        if pattern in line:
            print (line)


