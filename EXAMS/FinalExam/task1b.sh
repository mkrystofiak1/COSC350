#Program: task1b.sh
#Author: Mitchell Krystofiak
#Date: May 7, 2021

#!/bin/bash

sum=0

if [ $# -eq 0 ];
then 
	echo "No arguments!"
	exit 0;
fi

for i in "$@"
do
	sum=`expr $i + $sum`
done

echo "Sum of arguments: $sum"
