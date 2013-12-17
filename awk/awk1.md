Awk Notes
=========

**Pattern-Action Statement**

data1 contains employee name, salary per hour, number of hours worked

Program below gives non-zero salary for employees.
```
awk '$3 > 0 { print $1, $2 * $3 }' data1
```

`$3 > 0` is the pattern. Code inside `{ }` is the action. data1 is the input file.

Employess with 0 salary.
```
awk '$3==0 {print $1}' data1
```

Either the pattern or action in a patter-action statement may be omitted. `awk $3==0` prints the lines where the pattern matches. 

Since patters and actions are both optional. `{}` are used to distinguish between pattern and actions.


