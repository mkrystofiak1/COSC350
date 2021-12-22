//Program: ctrlc1.c
//Author: BLP 4th edition, Mitchell Krystofiak (edit)
//Description: Prints hello world until it gets a ctrlc signal.
//Date: March 31, 2021

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
}

int main()
{
	(void) signal(SIGINT, ouch);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
