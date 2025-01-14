#!/bin/sh

echo "enter pyramid size"
read size

if [ $size -lt 3 ]; then
    echo "size needs to be more than 3"
    exit 1
fi
if [ $(expr $size % 2) -eq '0' ]; then
    echo "size needs to be an odd number"
    exit 1
fi

for i in $(seq 1 $size)
do
    if [ $(expr $i % 2) -eq '0' ]; then
        continue
    fi

    for j in $(seq $i $size)
    do
        echo " \c ";
    done
    for k in $(seq 1 $i)
    do
        echo "* \c ";
    done
    echo;
done
