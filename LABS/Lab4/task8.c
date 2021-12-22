//Program: task8.c
//Author: Mitchell Krystofiak
//Description: This program will take in a text file and output file. Then write as integers.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
	int inFile, outFile, nread;
	int ch;
	int c;
	char buffer[1];
	
	if (argc != 3)
	{
		printf("Argument error! Expecting 2 arguments!\n");
		exit(1);
	}

	
	if ((inFile = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error opening input file.\n");
		exit(1);
	}
	else if ((outFile = open(argv[2], O_WRONLY)) == -1)
	{
		printf("Error opening output file.\n");
		exit(1);
	}
	
	dup2(outFile, 1);
	while((nread = read(inFile, buffer, 1)) > 0)
	{
		ch = *buffer;
		printf("%d ", ch);
	}

	close(inFile);
	close(outFile);

	exit (0);
}

