//Program: task6.c
//Author: Mitchell Krystofiak
//Description: Mutual exclusion stuff.
//Date: April 16, 2021

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

void* thread1()
{
	while (1)
	{
		pthread_mutex_lock(&count_mutex);
		//pthread_cond_wait( &condition_cond, &condition_mutex);
		if (count < 10)
			count++;
		printf("Counter in first thread = %d\n", count);
		pthread_mutex_unlock(&count_mutex);
		sleep(1);
	}
}

void* thread2()
{
	while (1)
	{
		pthread_mutex_lock(&count_mutex);
		
		if (count < 10)
			pthread_cond_signal(&condition_cond);
		if (count > 0)
			count--;
		printf("Counter in second thread = %d\n", count);
		pthread_mutex_unlock(&count_mutex);
		sleep(1);
	}
}

int main()
{
	pthread_t T1, T2;
	int counter = pthread_create(&T1, NULL, thread1, NULL);
	counter = pthread_create(&T2, NULL, thread2, NULL);
	
	if (counter)
	{
		printf("Pthread creation error!\n");
		exit(1);
	}
	pthread_join(T1,NULL);	
	pthread_join(T2,NULL);


	return 0;
}
