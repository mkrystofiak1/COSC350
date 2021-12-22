//Program: alarm.c
//Authors: BLP 4th edition, Mitchell Krystofiak (edit)
//Description: Edit alarm.c from reference to use sigaction.
//Date: March 31, 2021

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
	printf("\a");
}

int main()
{
	pid_t pid;

	struct sigaction alarm;
	alarm.sa_handler = ding;
	
	printf("alarm application starting\n");

	pid = fork();
	switch(pid) {
		case -1:
			/* Failure */
			perror ("fork failed");
			exit(1);
		case 0:
			/* child */
			sleep(5);
			kill(getppid(), SIGALRM);
			exit(0);
	}
	/* if we get here we are the parent process */
	printf("waiting for alarm to go off\n");

	sigaction(SIGALRM, &alarm, 0);
	
	pause();
	if (alarm_fired) 
		printf("Ding!\n");

	printf("done\n");
	exit(0);
}
