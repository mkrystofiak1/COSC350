//Program: process1.c
//Author: Mitchell Krystofiak
//Date: April 22, 2021

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>
#include"header.h"

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	struct Memory *shm;
	int num1;
	int num2;
	int n, more, i;

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
		exit (1);
	}

	shm->gostop = GO;
	shm->status = NOT_READY;
	
	for ( ; ;)
	{
		int temp;
		printf("Enter two integers.\n");
		temp = scanf(" %d%d", &num1, &num2);
		/*while (temp != 2)
		{
			printf("Invalid arguments. Enter two integers.\n");
			temp = scanf(" %d%d", &num1, &num2);
		}*/
		shm->data.value1 = num1;
		shm->data.value2 = num2;
		shm->status = FILLED;

		while (shm->status != TAKEN)
			;
		printf("Data is taken by other process\n");
	}

	shm->gostop = STOP;
	shmdt((void *) shm);
	return 0;
}
