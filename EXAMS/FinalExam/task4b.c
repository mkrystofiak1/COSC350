//Program: task4b.c
//Author: Mitchell Krystofiak
//Date: May 7, 2021

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SIZE 10
typedef int semaphore;
semaphore mutex = 0;
semaphore empty = 2;
semaphore full = 1;

union semun
{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
};

void up(int i, int semid)
{
        struct sembuf up = {i, 1, 0};
        semop(semid, &up, 1);
}

void down(int i, int semid)
{
        struct sembuf down = {i, -1, 0};
        semop(semid, &down, 1);
}

void handler(int sig)
{
	if (sig == SIGUSR1)
	{
		exit(0);
	}
}

void sigquit(int sig)
{
	if (sig == SIGCHLD)
	{
		exit(0);
	}
}

int main()
{
	union semun arg;
	key_t key = ftok("task4a.c", 'K');
	int semid = semget(key, 1, 0);

	pid_t pid = fork();

	if (pid == 0) //child
	{
		signal(SIGUSR1, handler);
		int loops = 0;
		while (1)
		{
			
			if (loops == 100)
			{
				kill(pid, SIGUSR1);
			}
			down(empty, semid);
			down(empty, semid);
			printf("Child is in critical section\n");
			up(mutex, semid);
			up(full, semid);
			sleep(1);
			loops++;
			
		}
	}
	else
	{
		while (1)
		{
			down(empty, semid);
			down(empty, semid);
			printf("Parent is in critical section\n");
			up(mutex, semid);
			up(full, semid);
			sleep(1);
			signal(SIGCHLD, sigquit);
		}
	}
	return 0;
}
