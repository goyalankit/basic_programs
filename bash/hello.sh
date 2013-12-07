numberToWord() {
    local arg1="$1"
    local value
    if ( test "$arg1" == "1"); then
        value="one"
    else if ( test "$arg1" == "2"); then
        value="two"
        fi
    fi
    echo "$value"
}

printNumberOfItems(){
    /bin/echo -n "I have these many items: "
    numberToWord 2
}

printNumberOfItems
