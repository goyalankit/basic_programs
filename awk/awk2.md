Fancier Output
==============

`printf(*format*, *value1*, *value2*, .. , *valueN*)` can be used. Similar to printf in C. Use format specifiers.

Examples:

`{printf("total pay for %s is $%.2f\n", $1, $2 * $3)}`

`{printf("%-8s $%6.2f\n", $1, $2 * $3)}` => `-` is used to left align.  Note the `$` in case of `%f`. 6 is the width of the characters. 2 is the decimal points that should be present.

Use the unix sort to sort.

`awk '{printf("$%6.2f %s\n", $2 * $3, $0)}' | sort` pipe the awk output to unix sort.


Selection
==========

* **Selection by Comparison**
    pattern of the form `$2 > 5` can be used to select by comparison.

* **Selection by Computation**
    Compute and then compare. For examples: `$2 * $3 > 50 {printf("$%6.2f %s", $2 * $3, $0)}`

* **Selection by text content**
    pattern like `$1 == "Susie"` can be used to match the text.
    You can also use **Regular Expressions!**
      Example: `awk '/Ma*/ {print $0}' data1` 
    Much more complex expressions can be searched using regular expressions.

* **Combination of patterns**
    
    Logical operators: `&&`, `||` and `!` are also available. Example: `$2 >= 4 || $3 >= 20`


**<----[Previous Fundamentals](awk1.md)**  **[Next Data validation](awk3.md) ---->** 
