//Program: task3.c
//Author: Mitchell Krystofiak
//Description: Palindrome checker.
//Date: March 10, 2021

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int palind(int fd1, int fd2)
{
	char buf1[1], buf2[1];

	lseek(fd1, 0, SEEK_SET);
	lseek(fd2, -3, SEEK_END);

	int a, b;
	int count = 0;
	int true = 1;
	while (true == 1)
	{
		lseek(fd1, count, SEEK_SET);
		a = read(fd1, buf1, 1);
		if (count == 0)
			lseek(fd2, -2, SEEK_END);
		else 
			lseek(fd2, (count+2)* -1, SEEK_END);

		b = read(fd2, buf2, 1);
		if(a == -1 || b == -1)
			return 0;
		count++;
		if (buf1[0] == '\n')
			break;

		if (buf1[0] != buf2[0])
			return 0;
	}
	return 1;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Error: Arugment error!\n");
		return 1;
	}

	int inFile, copy;

	if ((inFile = open(argv[1], O_RDONLY)) < 0)
	{
		printf("Error: Input file cannot be opened!\n");
		return 1;
	}
	copy = dup(inFile);

	if (palind(inFile, copy) == 1)
		printf("There exists a palindrome!\n");
	else
		printf("There does not exist a palindrome!\n");

	return 0;
}
		
