//Program: task5.c
//Author: Mitchell Krystofiak
//Description: sigprocmask
//Date: March 31, 2021

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void ProcessSignal(int sig)
{
	signal(SIGQUIT, SIG_DFL);
}

int main(int argc, char * argv[])
{
	sigset_t sigs;

	sigemptyset(&sigs); //clears signal set
	sigaddset(&sigs, SIGINT); //adds sigint to sigs
	sigaddset(&sigs, SIGQUIT); //adds sigquit to sigs
	sigprocmask(SIG_BLOCK, &sigs, 0); //blocks the signal in sigs
	

	//Loop 1: prints integers 1 to 5 at 1 second intervals, SIGINT and SIGQUIT are blocked
	for (int i = 1; i <= 5; i++)
	{
		printf("%d \n", i);
		sleep(1);
	}

	//unblock the signals
	signal(SIGQUIT, ProcessSignal);
	signal(SIGINT, ProcessSignal);

	sigprocmask(SIG_UNBLOCK, &sigs, 0);
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGINT);
	sigprocmask(SIG_BLOCK, &sigs, 0);

	//Loop 2: SIGINT is only one blocked (try sigint == Ctrl+C, sigquit == Ctrl+\)
	for (int i = 1; i <= 5; i++)
	{
		printf("%d \n", i);
		sleep(1);
	}

	exit(0);

}
