//Program: task5.c
//Author: Mitchell Krystofiak
//Description: This program will open a file and write into another in reverse order.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int input;
	int output;
	int buffer[1];
	int nread;
	int yes;
	
	if ((input = open("foo", O_RDWR)) == -1)
		write(2,"'foo' open error\n", 16);
	if ((output = open("foorev", O_RDWR | O_CREAT, 0760)) == -1)
		write(2,"'foorev' create error\n", 21);
	
	yes = lseek(input, 0, SEEK_END);
	while (yes >= 0)
	{
		lseek(input,yes,SEEK_SET);
		nread = read(input, buffer, 1);
		write(output, buffer, nread);
	        yes--;
	}

	close(input);
	close(output);
	exit (0);
}

