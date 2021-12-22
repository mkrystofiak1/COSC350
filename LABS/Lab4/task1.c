//Program: task1.c
//Author: Mitchell Krystofiak
//Description: Convert output of task #8 in Lab3 to origional file.
//Date: March 10, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

int str_to_int(char * ch)
{
	int x = 0;
	int number = 0;
	while (ch[x] != '\0')
	{
		number = 10 * number + (ch[x] - '0');
		x++;
	}
	return number;
}

void int_to_str(int x, char * str)
{
	int a = str_to_int(str);
	char temp = a;
	write(x, &temp, 1);
}

int main(int argc, char * argv[])
{
	int inFile, outFile, nread;
	int count = 0;
	char buf[1];
	int number = 0;

	if (argc != 3)
	{
		printf("Argument error! Expecting 2 arguments, the output from task#8!");
		return 1;
	}
	umask(0);
	if ((inFile = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error opening input file.\n");
		return 1;
	}
	else if ((outFile = open(argv[2], O_RDWR | O_CREAT, 0666)) == -1)
	{
		printf("Error opening output file.\n");
		return 1;
	}

	dup2(outFile, 1);
	while((nread = read(inFile, buf, 1) > 0))
	{
		if (number < 65 && buf[0] != ' ')
			number = number * 10 + (buf[0] - '0');
		else
		{
			printf("%c", number);
			number = 0;
		}
	}	
	close(inFile);
	close(outFile);

	return 0;	
	}

