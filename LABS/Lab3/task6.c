//Program: task6.c
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
	int pos;

        if ((input = open("foo", O_RDWR)) == -1)
                write(2,"'foo' open error\n", 16);
        if ((output = open("foorev", O_RDWR | O_CREAT, 0760)) == -1)
                write(2,"'foorev' create error\n", 21);
	
	while ((pos = pread(input,buffer,1,nread)) >= 0)
	{
		pwrite(output, nread, pos);
		nread--;
	}

	close(input);
	close(output);
	exit (0);
}
