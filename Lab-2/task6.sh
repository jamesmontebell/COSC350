#!/bin/sh
echo "input diamond size"

read size

if [ $size -lt 3 ]; then
	echo "size needs to be greater than three."
	exit 1
fi


if [ $(expr $size % 2) -eq "0" ] ; then
	echo "size needs to be an odd integer."
	exit 1
fi

#DIamond ----------------------------------------------

for i in $(seq 1 $size) # i = 1; i <= size; i++
do
	if [ $(expr $i % 2) -eq "0" ] ; then
		continue
	fi
    # print spaces
	for j in $(seq $i $size) # j = i; j <= size; j++
    do
      echo -n " ";
    done
	# print stars
	for k in $(seq 1 $i) # k = 1; i <= i; k++
    do
      echo -n "* ";
    done
    echo;
done
size1=$(expr $size - 1)
for i in $(seq $size1 -1 1) # i = 1; i <= size; i++
do
	if [ $(expr $i % 2) -eq "0" ] ; then
		continue
	fi
    # print spaces
	for j in $(seq $size -1 $i) # j = i; j <= size; j++
    do
      echo -n " ";
    done
	# print stars
	for k in $(seq $i -1 1) # k = 1; i <= i; k++
    do
      echo -n "* ";
    done
	echo
done

echo "#############################"

# Left-Arrow ----------------------------------------------



# Right-Arrow ----------------------------------------------

exit 0
