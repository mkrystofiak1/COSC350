//Program: task2c.c
//Author: Mitchell Krystofiak
//Date: May 7, 2021

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
        key = ftok(".", 'B');
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
		if (shm->status == STOP)
		{
			puts("Deleting shared memory and terminating!\n");
			break;
		}
                printf("Sum of integers: %d \n", (shm->data.value1 + shm->data.value2));
                shm->status = TAKEN;
        }
        shmdt ((void *) shm);
	shmctl(shmid, IPC_RMID, NULL);
        return 0;
}

