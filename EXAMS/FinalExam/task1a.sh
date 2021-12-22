#Program: task1a.sh
#Author: Mitchell Krystofiak
#Date: May 7, 2021

#!/bin/bash
echo "Subdirectories:"
echo
for i in *;
do
	if [ -d "$i" ]; 
	then
		echo "$i"
	fi
done

exit 0;
