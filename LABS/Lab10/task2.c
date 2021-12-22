//Program: task2.c
//Author: Mitchell Krystofiak
//Date: April 28, 2021

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

int buffer[10];
int ind = 0;

void print()
{
	int j;
	for (j = 0; j < 10; j++)
		printf("%d ", buffer[j]);
	printf("\n\n");
}

int produce_item()
{
	return rand() % 9 + 1;
}

void producer()
{
	int item;
	while (1)
	{
		item = produce_item();
		if (ind < 10)
		{
			buffer[ind++] = item;
			printf("Producing %d\n", item);
			print();
		}
		else
			printf("No space left in the buffer!\n");
		sleep(1);
	}
}

void consumer()
{
	while (1)
	{
		int x = buffer[ind - 1];
		if (ind > 0)
		{
			ind--;
			buffer[ind] = 0;
			printf("Consuming %d\n", x);
		}
		else
			printf("No value in buffer!\n");
		sleep(2);
	}
}

int main(int argc, char * argv[])
{
	pthread_t T[2];

	pthread_create(&T[0], NULL, producer, NULL);
	pthread_create(&T[1], NULL, consumer, NULL);

	pthread_join(T[0], NULL);
	pthread_join(T[1], NULL);

	return 0;
}

