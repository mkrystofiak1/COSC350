#!/bin/bash
#Program: task6b.sh
#Author: Mitchell Krystofiak
#Description: This program will print a left arrow based on length of tail and base.
#Date: February 17, 2021

read -p "Enter the size of the base: " base

if [ `expr $base % 2` -eq 0 ]
then
        echo "Base must be odd."
        exit 1
elif [ $base -le 0 ]
then
        echo "Base must be positive and greater than zero."
        exit 1
fi

read -p "Enter the length of the tail: " tail

if [ $tail -lt 0 ]
then
	echo "Tail must be positive."
        exit 1
fi
middle=`expr $base + $tail`
middle2=`expr $middle \* 2`
tail2=`expr $tail \* 2`

for i in $(seq 1 2 $base)
do
	if [ `expr $i % 2` -eq 0 ]
	then
		continue 2
	fi
	if [[ $i -ne $base && $i -lt $base ]]
	then
		k=`expr $base - $i`
		k=`expr $k \* 2`
		for j in $(seq 1 2 $k) #((j=1; j<=$base-$i;j++))
		do
			echo -n "  "
		done
		k=`expr $i \* 2`
		for j in $(seq 1 2 $k) #((j=1; j<=$i; j++))
		do
			echo -n "* "
		done
		echo
	fi
	if [ $i -eq $base ]
        then
                for j in $(seq 1 2 $middle2) #((j=1; j<=$middle; j++))#middle line
                do
                        echo -n "* "
                done
                echo
        fi
done
for i in $(seq 1 2 $base) #((i=1; i<=$base; i++))
do
	if [ `expr $i % 2` -eq 0 ]
	then
		continue 2
	fi
	k=`expr $i \* 2`
	for j in $(seq 0 2 $k) #((j=0; j<=$i; j++))
	do
		echo -n "  "
	done
	k=`expr $base - $i - 1`
	k=`expr $k \* 2`
	for j in $(seq 1 2 $k) #((j=1; j<=$base-$i-1; j++))
	do
		echo -n "* "
	done
	echo
done

exit 0
