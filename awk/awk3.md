Data Validation
===============

Multiple patters can be applied. 
```
NF != 3 { print $0, "number of fields are not equal to 3" }
$2 < 3.3 { print $0, "the second parameter is less than 3.3"}
```

BEGIN and END
=============

The special `BEGIN` matches before the first line of the first input file is read, and `END` matches after the last line has been processed.

Examples:
`awk 'BEGIN { print "NAME RATE HOURS"; print "" } { print } END {print "I am going to end now"}' data1`

`print ""` prints a blank line as opposed to `print` which prints the current input line.

Computing with AWK
==================

You can create your own variables for performing calculations, storing data, etc.

* User-created variables are not declared.
* Variables are initialized to 0. No need to initialize explicitly.

In the following code, emp is the user-created variable. 
```
$3 > 15 {emp = emp + 1}
END {print emp, "employees worked for more than 15 hours."}
```

Handling Text
=============

```
$2 > maxrate { maxrate = $2, maxemp = $1 }
END { print "highest salary rate: ", maxrate, "for", $1 }
```

String Concatenation
====================

Concatenation is represented by writing string values one after the another.

```
{ names = names $1 " "}
END { print names }
```

```
{print "Ankit" " " "Goyal" }
```

Printing the last Input line
============================

unlike `NR`, `$0` **DOESN'T** retain its value in the `END`.

```
{last = $0}
END {print last}
```

**<---- [Fancier Output](awk2.md)**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
**[Functions](awk4.md) ---->** 
