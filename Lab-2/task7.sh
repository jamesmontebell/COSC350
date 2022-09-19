#!/bin/sh

echo "Calculate Factorial: "

read num

tot=1

while [ $num != "0" ] ;
do
    tot=$(expr $tot \* $num)
    num=$(expr $num - 1)
done

echo "$tot"

exit 0