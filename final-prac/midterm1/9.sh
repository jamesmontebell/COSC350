#!/bin/sh

if [ $# -eq 0 ]; then
    echo "enter numbers"
    exit 1
fi


sum=0
for i in $@
do
    if [ $(expr $i % 2) -eq 0 ]; then
        sum=$(expr $sum + $i)
    fi
done

echo "$sum"

you=Michael
x=you
y=x
z=\$$y
echo $z

you=Michael
x=you
y=x
eval z=\$$y
echo $z


echo "\$$x"




exit 0 