//Program: task1.c
//Author: Mitchell Krystofiak
//Description: Copy content of a readable file to a file without opening input files.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
	int input;
	char buffer[128];
	input = read(0, buffer, 128);
	if (input < -1)
		write (2, "A read error\n", 12);

	if ((write(1, buffer, input))!= input)
		write (2, "A write error\n", 13);
	
	exit (0);	
}
