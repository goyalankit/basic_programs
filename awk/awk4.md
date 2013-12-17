Functions
=========

####Built-in Functions####

**`length`** : length of a given string.

`{ print $1, length($1) }`

#####Counting lines, words and characters#####

```
{
    nc = nc + length($0) + 1
    nw = nw + NF
}

END { print NR, "lines,", nw, "words,", nc, "characters" }
```

`$0` doesn't include new line character. so `+1` in above `nc` counter.


Control-Flow Statements
=======================

if-Else, loops are modeled on C language.

####if-Else statements####

```
$2 > 6 { n = n + 1; pay = pay + $2 * $3}
END { if (n>0)
        print n, "employees have more than $6 salary", "Average salary
        is", pay/n 
      else
        print "no employee has salary more than $6"
    }
```

####while####

Sample code and data in `awk4_loop` and `awk4_loop.data`

```
{
    i = 0
        while ( i< $3 ){
            printf("single record is getting printed for %f times\n", $3)
                i = i + 1
        }
}
```

####for####

Sample code and data in `awk4_4loop` and `awk4_loop.data`

```
{
    for (i=1; i<=$3; i = i + 1)
        printf("single record is getting printed for %f times n", $3)

}

```

Arrays
======

Print the input in reverse order by line
```
{ line[NR] = $0 }
END{ i = NR
     while (i > 0){
        print line[i]
        i = i - 1
    }
}

```

**<---- [Data Validation](awk3.md)**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
**[Useful One Liners](awk5.md) ---->** 
