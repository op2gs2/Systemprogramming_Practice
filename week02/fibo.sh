#!/bin/bash
echo -n "Input Number: "
read num
result=0

if [ "$num" = 1 ]
then
    result=1
else
    # "declare -i" makes integer variable.
    # "declare" isn't work on "sh". 
    # instead, you can use this keyword in "bash native" (./)
    declare -i iterA=0
    declare -i iterB=1
    # This is another way to execute "for".
    # First, set-up range in a particular variable
    # Second, apply in the "for" statement.
    # other things aren't different as normal "for".
    c=2
    set=$(seq $c $num)
    for i in $set
    do
        result=$(( $iterA+$iterB ))
        iterA=iterB;
        iterB=result;
    done
fi
echo "Result: $result"
exit 0

# If you have an error "bad interpreter: No such file or directory",
# You should remove "^M" from "vi -b".