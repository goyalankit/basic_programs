1. coroutine: you send value as apposed to receiving in case of generators.

```
def grep(pattern):
	print ('Looking for ', pattern)
	while True:
		line = (yield)
		if pattern in line:
			print (line)

> g = grep('python')
> g.next() # Advance to the yield.

> g.send("python is okay")
python is okay

```

decorator `@coroutine` will launch the code for you. It will call next for you.

2. Couroutines tend to consume values. Usually not in the conext of for loops/iteration.
3. Generators produce values.

