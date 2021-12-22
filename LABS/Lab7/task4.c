//Program: task4.c
//Author: Mitchell Krystofiak
//Description: Using signal and kill system calls
//Date: March 31, 2021

#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void ProcessSignal(int sig)
{
	if (sig == SIGUSR1) //if first child send message sigusr1 to parent
		printf("Hi Honey! Anything wrong?");
	else if (sig == SIGUSR2) //if second child send message sigusr2 to parent
		printf("Do you make trouble again?");
}

int main(int argc, char * argv[])
{
	pid_t pid1;
	pid_t pid2;
	
	pid1 = fork();
	if (pid1 < 0)
	{
		printf("Fork failed.\n");
		exit(1);
	}
	else if (pid1 == 0)
	{
		kill(pid1, SIGUSR1);
		pause();
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
		{
			printf("Fork failed.\n");
			exit(1);
		}
		else if (pid2 == 0)
		{
			kill(pid2,SIGUSR2);
			pause();
		}
		else
		{
			signal(SIGUSR1, ProcessSignal);
			signal(SIGUSR2, ProcessSignal);
		}
	}

	exit(0);
}

