//Program: process2.c
//Author: Mitchell Krystofiak
//Date: April 22, 2021

#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include"header.h"

int main(int argc, char * argv[])
{
	int shmid, n, int1, int2;
	key_t key;
	struct Memory *shm;
	key = ftok(".", 'x');
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0)
	{
		perror("shmget error \n");
		exit (1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long)shm == -1)
	{
		perror("shmat error \n");
		exit(1);
	}

	while (shm->gostop == GO)
	{
		while (shm->status != FILLED)
		{
			if (shm->gostop == STOP)
				break;
			;
		}
		printf("Integer 1: %d \n", shm->data.value1);
		printf("Integer 2: %d \n", shm->data.value2);
		printf("Sum of integers: %d \n", (shm->data.value1 + shm->data.value2));
		shm->status = TAKEN;
	}
	shmdt ((void *) shm);

	return 0;
}
