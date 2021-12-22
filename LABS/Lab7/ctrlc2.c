//Program: ctrlc2.c
//Author: BLP 4th edition, Mitchell Krystofiak (edit)
//Description: Runs similar to ctrlc1.c, but this time it won't end with the second ctrl+C, instead ctrl+\
//Date: 03/31/2021

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch (int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
	signal(SIGINT, SIG_DFL); //converts ctrl+C back to normal
}

int main()
{
	struct sigaction act;
	
	//this set of code calls the ouch function when an action is performed
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	//this sets ctrl+c to call the ouch function
	sigaction(SIGINT, &act, 0);


	//this sets ctrl+\ to call the ouch function
	//sigaction(SIGQUIT, &act, 0);
	
	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
