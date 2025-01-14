#!/bin/sh

if [ -z $@ ]; then # -z true if string is null
    echo "there are no arguments on command line"
    exit 0
fi

sum=0

for i in $@
do 
    if [ $(expr $i % 2) -eq '0' ]; then
        sum=$(expr $sum + $i)
    fi
done
echo "sum is $sum"

exit 1
