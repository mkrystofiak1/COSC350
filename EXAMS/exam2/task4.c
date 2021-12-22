//Program: task4.c
//Author: Mitchell Krystofiak
//Description: Parent/child running same time...
//Date: April 16, 2021

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handler(int sig)
{
	if (sig == SIGUSR1)
	{
		printf("From now on, I am a Zombie\n");
		exit(0);///
	}
}

int main()
{
	
	int status = 0;	
	pid_t pid = fork();
	
	if (pid == 0) //child
	{
		signal(SIGUSR1, handler);

		while (1)
		{
			printf("I am your child\n");
			sleep(1);
		}
	}
	else if (pid > 0) //parent
	{
		for (int i = 0; i < 10; i++)
		{
			printf("I am your parent\n");
			sleep(1);
		}

		
		exit(0);
	}
	return 0;
}

