#!/bin/bash

#Program: task6a.sh
#Author: Mitchell Krystofiak
#Description: Outputs a diamond of a specific size.
#Date: February 17, 2021

read -p "Enter the size of the base: " base

if [ `expr $base % 2` -eq 0 ]
then
	echo "Base must be odd."
	exit 1
fi

for i in $(seq 1 2 $base) #((i=1; i<=$base; i++))
do
	if [ `expr $i % 2` -eq 0 ]
	then
		continue 2
	fi
	for j in $(seq $base -1 $i) #((j=$base; j>=i; j--))
	do
		echo -n " "
	done
	k=`expr $i \* 2`
	for j in $(seq 1 2 $k) #((j=1; j<=i; j++))
	do
		echo -n " *"
	done
	echo
done
dmax=`expr $base - 1`
for i in $(seq $dmax -1 1) #((i=$dmax; i>=1;i--))
do
	if [  `expr $i % 2` -eq 0 ]
	then
		continue 2
	fi
	for j in $(seq $i $dmax) #((j=i; j<=$dmax;j++))
	do
		if [ $j -eq $dmax ]
		then
			echo -n " "
		fi
		echo -n " "
	done
	k=`expr $i \* 2`
	for j in $(seq 1 2 $k) #((j=1; j<=i; j++))
	do
		echo -n " *"
	done
	echo
done
exit 0
