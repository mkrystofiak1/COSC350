//Program: task2.c
//Author: Mitchell Krystofiak
//Description: Wait for a Thread for Concurrent Calculations:
//	1. Get test scores from keyboard up to 20 and save into array.
//	2. Calculate an average score and Medium value and display.
//	3. Get the minimum and the maxium score and display.
//	4. Clear buffer and set to 0 and display after 2,3 finishes the job.
//
//Date: April 7, 2021

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

void get_scores(int * scores)
{
	int score;
	int valid = 1;
	int i;

	for (i = 0; i < 20 && valid; i++)
	{
		printf("Enter test score %d (-1 to stop): ", i+1);
		scanf("%d", &score);
		while (score < -1)
		{
			printf("Score must be positive!\n");
			scanf("%d", &score);
		}
		scores[i] = score;
		if (score == -1)
			valid = 0;
	}
	i--;

	for (int j = 0; j < i - 1; j++)
	{
		int min = j;
		for (int n = j + 1; n < i; n++)
		{
			if (scores[n] < scores[min])
				min = n;
		}
		int x = scores[j];
		scores[j] = scores[min];
		scores[min] = x;
	}
	pthread_exit(0);
}

void get_average(int * scores)
{
	int i;
	int totalScores = 0;
	double average, medium;

	for (i = 0; scores[i] != -1; i++)
		totalScores += scores[i];

	if (i == 0)
	{
		printf("Scores array is empty, thus average = 0, medium = 0.\n");
		pthread_exit(0);
	}

	average = (double)totalScores / i;

	if (i % 2 == 0)
	{
		int rhs = (i/2)-1;
		int lhs = (i/2);
		medium = (double)(scores[rhs] + scores[lhs]) / 2;
	}
	else
		medium = scores[i/2];

	printf("Average score: %2.2f \t\t Median score: %2.2f\n", average, medium);
	pthread_exit(0);
}

void get_minmax(int * scores)
{
	int i;
	int max;

	int min = scores[0];

	for (i = 0; scores[i] != -1; i++)
		max = scores[i];

	if (i == 0)
	{
		printf("Scores array is empty, thus no max or min.\n");
		pthread_exit(0);
	}

	printf("Lowest score: %d \t\t Highest score: %d\n", min, max);
	pthread_exit(0);
}

void clear(int * scores)
{
	printf("Clearing Buffer\n");

	for (int i = 0; i < 20; i++)
	{
		scores[i] = 0;
		printf("%d ", scores[i]);
	}
	printf("\n");
	pthread_exit(0);
}

int main(int argc, char * argv[])
{
	pthread_t Thread[4];
	int code;
	int i;

	int* scores = malloc(20 * sizeof(int));
	
	code = pthread_create(&Thread[0], 0, get_scores, (void *)scores);
	if (code)
	{
		printf("Get scores thread error.\n");
		exit(1);
	}

	pthread_join(Thread[0], 0);

	code = pthread_create(&Thread[1], 0, get_average, (void *)scores);
	if (code)
	{
		printf("Get average/medium thread error.\n");
		exit(1);
	}

	code = pthread_create(&Thread[2], 0, get_minmax, (void *)scores);
	if (code)
	{
		printf("Min/max thread error.\n");
		exit(1);
	}

	pthread_join(Thread[1], 0);
	pthread_join(Thread[2], 0);

	code = pthread_create(&Thread[3], 0, clear, (void *)scores);
	if (code)
	{
		printf("Clear buffer thread error.\n");
		exit(1);
	}

	pthread_join(Thread[3], 0);
	pthread_exit(0);

	exit(0);
}
