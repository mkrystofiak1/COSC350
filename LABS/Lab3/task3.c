//Program: task3.c
//Author: Mitchell Krystofiak
//Description: This program will copy content of file to clone2.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int input;
	int output;
	int buffer[32];
	int nread;

	input = open("foo", O_RDWR);
	if (input < 0)
		write(2, "An open error\n", 13);

	output = open("clone2", O_RDWR | O_CREAT, 0770);
	if (output < 0)
		write(2, "File already exists\n", 19);

	while ((nread = read(input, buffer, 1)) > 0)
		write(output, buffer, nread);

	close(input);
	close(output);

	exit (0);
}
