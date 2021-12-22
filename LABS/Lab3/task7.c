//Program: task6.c
//Author: Mitchell Krystofiak
//Description: This program will open a file and write into another in reverse order.
//Date: February 24, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int st_to_it(char * str)
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		result = result*10 + str[i] - '0';

	return result;
}

int main(int argc, char* argv[])
{
	int sum = 0;
	int temp;
	if (argc == 1)
	{
		printf("Error: No arguments!\n");
		exit(1);
	}
	for (int i = 1; i < argc; i++)
	{
		temp = st_to_it(argv[i]);
		sum = sum + temp;
	}
	
	printf("The sum of the numbers is: %d", sum);
	printf("\n");
		
	exit (0);
}
