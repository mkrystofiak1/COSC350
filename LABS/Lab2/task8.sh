#!/bin/bash
#Program: task8.sh
#Author: Mitchell Krystofiak
#Description: This program will add up the digits of an integer.
#Date: February 17, 2021

read -p "Enter an integer:" num arg2

if [ -z $num ]
then
	echo "String is null."
	exit 1
elif [ $arg2 ]
then
	echo "Only one numerical argument allowed."
	exit 1
fi

sum=0

while [ $num -gt 0 ]
do
	k=`expr $num % 10`
	num=`expr $num / 10`
	sum=`expr $sum + $k`
done
echo "Sum of digits = $sum"

exit 0
