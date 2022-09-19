#!/bin/sh

echo "Enter integer: "

read num

sum=0

if [ -z $num ]; then
    echo "You need to pass one numerical argument."
fi

while [ $num -gt "0" ] ; 
do
    k=$(expr $num % 10)
    sum=$(expr $sum + $k)
    num=$(expr $num / 10)
done

echo "The sum is $sum."

exit 0