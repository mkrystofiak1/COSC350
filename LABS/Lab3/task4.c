//Program: task4.c
//Author: Mitchell Krystofiak
//Description: This program will open 2 files and append content of files to foo12.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int input1; //input file 1 == foo
	int input2; //input file 2 == foo1
	int output; //output file == clone2
	int nread;
	int yes;
	char buffer[1]; //buffer message
	char buffer2[128];
	
	//open and create ouput file
	if ((output = open("foo12", O_RDWR | O_CREAT | O_APPEND, 0760)) == -1)
		write(2,"Error creating file 'foo12'\n", 27);
	//open input1
	if ((input1 = open("foo", O_RDWR )) == -1)
		write(2,"Error opening file 'foo'\n", 24);
	//open input2
	if ((input2 = open("foo1", O_RDWR)) == -1)
		write(2,"Error opening file 'foo1'\n", 23);
	
	//lseek format == lseek(file to , how far to go, where to start from)
	
	while ((nread = read(input1, buffer, 1)) > 0)
		write(output, buffer, nread);

	yes = lseek(input1, 0, SEEK_END );	
	lseek(output, yes, SEEK_SET);
	
	while ((nread = read(input2, buffer, 1)) > 0)
		write(output, buffer, nread);
	
		
	close(input1);
	close(input2);
	close(output);
	exit (0);
}
