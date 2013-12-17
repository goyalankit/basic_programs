Useful one-liners
=================

* Print the total number of lines ` END { print NR } `
* Print the 10 input line ` NR == 10 `
* Print the last field of every input line ` { print $NF } `
* Print the last field of last input line ` { lastfield = $NF } END { print lastfield } `
* Print every input line with more than 4 fields ` NF > 4 `
* Print every input line in which last input is more than 4 ` $NF > 4 `
* Print the total number of files in all input lines. ` {nf = nf + NF } END { print nf } `
* Print the total number of lines that contains *Beth* ` /Beth/ { n = n + 1 } END { print n } `
* Print the largest first field and the line that contains it. `$1 > max {max = $1; line = $0} END {print "largest field", max, "on line", line }`
* Print every line that has at least 1 field. ` NF > 0 `
* Print every line longer than 80 characters. ` length($0) > 80`
* Print the number of fields in every line followed by the line itself.  `{print NF, $0}`
* Print the first two fields in opposite order, of every line. `{print $2, $1}`
* Exchange the first two fields of every line and then print it. `{ temp = $1; $1 = $2; $2 = temp; print }`
* Print every line with the first field replaces by line number. `{$1 = NR; print}`
* Print every line after erasing the second fields. `{$2 = ""; print}`
* Print the reverse order of fields in every line.

```
{
    for( i = NF; i > 0; i = i - 1) 
    printf("%s ",i)
    printf("\n") 
}

```

* Print the sum of the fields of every line

```
{
    sum = 0
    for (i = 1; i <= NF; i = i + 1)
        sum = sum + $i
    print sum
}
```

* Add up all fields in all lines and print the sum

```
{
    
    for (i = 1; i <= NF; i = i + 1)
        sum = sum + $i
    END{print sum}
        
}
```

* Print every line after replacing each field by its absolute value

```
{
    for(i=1; i<=NF ; i = i + 1) if($i < 0 ) $i = -$i
    print   
}
```

**<---- [Functions](awk4.md)**
