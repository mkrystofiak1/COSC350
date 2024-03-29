//Program: task3.c
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
#include <sys/msg.h>

#define N 10
typedef int semaphore;
semaphore mutex = 0;
semaphore empty = 2;
semaphore full = 1;

int semid;
int list[10];
int curr = 0;

typedef union SEMUN
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
} Semun;

void insert_item(int item)
{
	if (curr < 10)
		list[curr++] = item;
	else
		printf("No space to insert. \n");
}

int remove_item()
{
	if (curr >= 0)
	{
		int temp = list[curr - 1];
		curr--;
		list[curr] = 0;
		return temp;
	}
	else
		printf("No value to remove\n");
}

void up(int sem_num)
{
	struct sembuf up = {sem_num, 1, 0};
	if (semop(semid, &up, 1) == -1)
	{
		perror("semop() error!\n");
		exit(1);
	}
}

void down(int sem_num)
{
	struct sembuf down = {sem_num, -1, 0};
	if (semop(semid, &down, 1) == -1)
	{
		perror("semop() error!\n");
		exit(1);
	}
}

void* producer()
{
	int item;
	while(1)
	{
		item = rand() % 9 + 1;
		down(empty);
		down(mutex);
		printf("Producing %d\n", item);
		insert_item(item);
		up(mutex);
		up(full);
		int i;
		for (i = 0; i < 10; i++)
			printf("%d ", list[i]);
		puts("");
		sleep(1);
	}
}

void* consumer()
{
	int item;
	while(1)
	{
		down(full);
		down(mutex);
		item = remove_item();
		up(mutex);
		up(empty);
		printf("Consuming %d\n", item);
		int i;
		for (i = 0; i < 10; i++)
			printf("%d ", list[i]);
		puts("");
		sleep(2);
	}
}

int main(int argc, char* argv[])
{

	key_t key;
	if ((key = ftok("task3.c", 'B')) == -1)
	{
		perror("ftok() error!\n");
		exit(1);
	}

	if ((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1)
	{
		perror("semget() error");
		exit(1);
	}

	Semun arg;
	arg.val = 1;
	if (semctl(semid, mutex, SETVAL, arg) == -1)
	{
		perror("semctl() error!\n");
		exit(1);
	}
	arg.val = 0;
	if (semctl(semid, full, SETVAL, arg) == -1)
	{
		perror("semctl() error!\n");
		exit(1);
	}
	arg.val = 0;
	if (semctl(semid, full, SETVAL, arg) == -1)
	{
		perror("semctl() error!\n");
		exit(1);
	}
	arg.val = 10;
	if (semctl(semid, empty, SETVAL, arg) == -1)
	{
		perror("semctl() error!\n");
		exit(1);
	}

	pthread_t T[2];

	pthread_create(&T[0], NULL, producer, (void*)&semid);
	pthread_create(&T[1], NULL, consumer, (void*)&semid);

	pthread_join(T[0], NULL);
	pthread_join(T[1], NULL);

	if (semctl(semid, 0, IPC_RMID, arg) == -1)
	{
		perror("semctl() error!\n");
		exit(1);
	}
	
	return 0;
}

