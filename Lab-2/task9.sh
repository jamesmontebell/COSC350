#!/bin/sh

echo "Enter directory: "
read direc

if [ $(expr substr $direc 1 1) = "~" ] ; then
    direc=$HOME
fi

if [ ! -d $direc ] ; then
    echo "1 no such directory"
    exit 1
fi


try=3
while [ $try -gt 0 ] ;
do
    echo "Enter valid filename: "
    read name
    name=$direc/$name
    if [ -f "$name" ] ; then
        if [ ! -r $name ] ; then
            echo "3 file is not readable."
            exit 3
        fi
        try=$(expr $try - 3)
        break
    fi
    try=$(expr $try - 1)
    if [ $try = 0 ] ; then
        echo "2 no such file (after three attempts)"
        exit 2
    fi
done

echo "Enter word to find in file: "
read word

if grep -q $word $name ; then
    echo "$word FOUND!"
else
    echo "$word NOT FOUND!"
    echo "4 word not found"
fi


exit 0
