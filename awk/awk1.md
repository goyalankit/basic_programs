Fundamentals of AWK
===================

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

Either the pattern or action in a patter-action statement may be omitted. `awk '$3==0'` prints the lines where the pattern matches. 

Since patters and actions are both optional. `{}` are used to distinguish between pattern and actions.

---

Run the awk program
===================

* `awk 'program' *input files*` => `awk '$3==0' file1 file2`
* `awk 'program'` => it will run the program on each line that you type.
* `awk -f progfile *input files*` => `progfile` is the filename that contains the awk code.

---

* There are only two types of data in awk. `Numbers` and `String of characters`.
* The first field is `$1`, and then next is `$2`. 
* `$0` is the entire line.
* Number of fields can vary from line to line. Awk parses each line and then apply action.
* built-in variable `NF` could be used to get number of  fields. Hint: use `$NF` to print the last field.
* built-in variable `NR` keeps track of number of rows that the awk has read. => `{print NR, $0}` prints the line number followed by the line.
* You can put the text between the fields. `{print "total pay for", $1, "is", $2 * $3}`

Next set of notes include fancier output for awk.
