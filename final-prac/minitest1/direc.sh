#!/bin/sh

for i in *
do 
    if [ -d $i ]; then
        echo "$i"
    fi
done
exit 0