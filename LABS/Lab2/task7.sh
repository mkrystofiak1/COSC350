#!/bin/bash
#Program: task7.sh
#Author: Mitchell Krystofiak
#Description: Uses while loop to print the factorial of a number.
#Date: February 17, 2021

read -p "Input a number: " number

num=$number

if [[ $number -eq 0 || $number -eq 1 ]]
then
	echo $number"! = 1"
	exit 0
elif [[ $number -lt 0 ]]
then
	echo "Number cannot be negative."
	exit 1
fi

fact=1

while [ "$number" -gt 1 ];
do
	fact=`expr $fact \* $number`
	number=`expr $number - 1`
done

echo "$num! = $fact"

exit 0
