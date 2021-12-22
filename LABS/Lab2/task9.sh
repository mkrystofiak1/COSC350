#!/bin/bash
#Program: task9.sh
#Author: Mitchell Krystofiak
#Description: This program will search for a word in a file.
#Date: February 17, 2021

read -p "Enter the directory in which to find the file: " dir

if [ -d $dir ]
then
	read -p "Enter the name of a readable file in the directory given: " file
	tries=1
	while [ $tries -lt 3 ]
	do
		if [ -e $dir/$file ]
		then 
			if [ -r $dir/$file ]
			then
				break 
			fi
		fi
		read -p "File $file does not exist or it is not readable. Try again: " file
		tries=`expr $tries + 1`
	done
	if [ -e $dir/$file ]
	then
		if [ -r $dir/$file ]
		then
			read -p "Enter a word to find in the file: " word
			if grep -q $word $dir/$file
			then
				echo "$word FOUND!"
				exit 0
			else
				echo "$word NOT FOUND!"
				exit 4
			fi
		else
			echo "File $file is not readable."
			exit 3
		fi
	else
		echo "File $file does not exist and you've exceeded max tries."
		exit 2
	fi
else
	echo "Directory $dir does not exist."
	exit 1
fi

exit 0
