#!/bin/bash
#Program: task6c.sh
#Author: Mitchell Krystofiak
#Description: This program will print a right arrow based on length of tail and base.
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
for i in $(seq 1 2 $base) #((i=1; i<=$base; i++))
do
	if [ `expr $i % 2` -eq 0 ] #odd lines only
	then 
		continue 2
	fi
	if [[ $i -ne $base && $i -lt $base ]]
        then
		for g in $(seq 1 2 $tail2) #((g=1; g<=$tail*2 ;g++))#top of arrow
                do
  	              echo -n "  "
                done
		k=`expr $i \* 2`
		for j in $(seq 1 2 $k) #((j=1; j<=i; j++))
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
i=`expr $base - 1`
for i in $(seq $i -1 1) #((i=$base-1; i>=1; i--))
do
	if [ `expr $i % 2` -eq 0 ]
	then
		continue 2
	fi
	
	for g in $(seq 1 2 $tail2) # ((g=1; g<=$tail*2; g++))
	do
		echo -n "  "
	done
	k=`expr $i \* 2`
	for j in $(seq 1 2 $k)  #((j=1; j<=i; j++))
	do
		echo -n "* "
	done
	echo
done
exit 0
