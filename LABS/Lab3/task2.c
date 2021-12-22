//Program: task2.c
//Author: Mitchell Krystofiak
//Description: Copy content of a readable file to a file with opening input files.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int input;
	int output;
	int nread;
	char buffer[128];

	input = open("foo", O_RDWR);
	output = open("clone1", O_RDWR | O_CREAT, 0666);
	if (input < 0)
		write (2, "An open error\n", 13);
	
	if (output < 0)
		write (2, "File already exists\n", 19);

	while ((nread = read(input, buffer, 1)) > 0)
		write(output, buffer, nread);
		
	close(input);	
	close(output);

	exit (0);
}
