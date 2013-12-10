#/bin/bash
#different syntax for conditional statements

variable=2

echo "----------------------------------------"
echo "Type of conditionals supported by shell!"
echo "----------------------------------------"

if ( test  "$variable" == 2 ); then
    echo "1:   (test \"\$variable\" == 2) condition passed"
fi

if (( "$variable" == 2 )); then
    echo "2:   (( \"\$variable\" == 2)) condition passed"
fi

#if ("$variable" == 2); then
    echo "3:   ( \"\$variable\" == 2 ) condition NOT passed"
#fi

if [ "$variable" == 2 ]; then
    echo "4:   [ \"\$variable\" == 2 ] condition passed"
fi

if test  "$variable" == 2; then
    echo "5:   test \"\$variable\" == 2 condition passed"
fi

#An awesome way! The one liner
[ "$variable" == 2 ] &&  echo "6:   [ \$variable == 2 ] && echo condition passed"

myString="/etc/rc2.d"

#Regular Expressions.
if [[ $myString =~ /etc/rc\d*..d ]]; then
    echo "6:  [[ ]] brackets and =~ can be used to match regular expressions"
fi

echo "--------------------------"
echo "other conditional options!"
echo "--------------------------"

if [ -z "$MY_ENV" ]; then echo "empty or unset"; fi

if [ "$MY_ENV" == "" ]; then echo "empty or unset"; fi

if [ -z "${MY_ENV+xxx}" ]; then echo "just unset and not empty"; fi
