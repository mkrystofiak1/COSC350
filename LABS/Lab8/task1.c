//Program: task1.c
//Author: Mitchell Krystofiak
//Description: Concurrent Calculation, accepts integer argument and calculate sum up and factorial using threads.
//Date: April 7, 2021

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *Sum(void *n)
{
	int sum = (int)n;
	for (int i = sum - 1; i > 0; i--)
		sum += i;
	n = (void *)sum;
	return n;
}

void *Factorial(void *n)
{
	int product = (int)n;
	for (int i = product - 1; i > 0; i--)
		product *= i;
	n = (void *)product;
	return n;
}

int str_to_int(char* str)
{
	int n = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return n;
}

int main(int argc, char * argv[])
{
	pthread_t sumT, factT;
	int code;

	if (argc != 2)
	{
		printf("Argument Error!\n");
		exit(1);
	}

	int num = str_to_int(argv[1]);

	code = pthread_create(&sumT, 0, Sum, (void *)num);
	if (code)
	{
		printf("Error with pthread for sum!\n");
		exit(1);
	}
	
	code = pthread_create(&factT, 0, Factorial, (void *)num);
	if (code)
	{
		printf("error with pthread for factorial!\n");
		exit(1);
	}

	void *sum;
	void *fact;

	pthread_join(sumT, &sum);
	pthread_join(factT, &fact);
	
	printf("Sum: %d\n", (int)sum);
	printf("Factorial: %d\n", (int)fact);

	exit(0);
}
