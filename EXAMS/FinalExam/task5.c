//Program: task5.c
//Author: Mitchell Krystofiak
//Date: May 7, 2021

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int sig)
{
	if (sig == SIGUSR1)
	{
		printf("I am terminated by my parent\n");
		exit(0);
	}
}

void sigquit(int sig)
{
	if (sig == SIGCHLD)
	{
		printf("My child is gone so I am now\n");
		exit(0);
	}
}

int main()
{
	int status = 0;

	pid_t pid;
	if ((pid = fork()) < 0)
	{
		printf("Fork error!\n");
		exit(1);
	}
	
	if (pid == 0) //child process
	{
		signal(SIGUSR1, handler);

		while (1)
		{
			printf("child is running\n");
			sleep(1);
		}
	}
	else //parent process
	{
		int count = 0;
		while (1)
		{
			if (count == 10)
				kill(pid,SIGUSR1);
			printf("parent is running\n");
			sleep(1);
			count++;
			signal(SIGCHLD, sigquit);
		}
	}
	exit(0);
}
