//Program: forkExec.c
//Authors: reference.pdf; Mitchell Krystofiak (edit)
//Desciption: Edited forkWait to take in line arguments and run child.c separately.
//Date: March 24, 2021

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int str_to_int(char * ch)
{
	int x = 0;
	int number = 0;
	while (ch[x] != '\0')
	{
		number = 10 * number + (ch[x] - '0');
		x++;
	}
	return number;
}

int main(int argc, char * argv[])
{
	if ( argc != 5 ) //five arguments
	{
		printf("Error: Expecting 4 inputs!\n");
		exit(1);
	}

	pid_t pid;
	char *message;
	int Nc = str_to_int(argv[1]);
	int Np = str_to_int(argv[2]);
	int Tc = str_to_int(argv[3]);
	int Tp = str_to_int(argv[4]);
	int slp;
	int exit_code;
	int n;
	printf("fork program starting\n");
	pid = fork();
	switch(pid) 
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			execlp("./child", argv[1], argv[3], "This is the child", (char *)0);
			break;
		default:
			for (; Np > 0; Np--)
			{
				printf("Parent ID = %d. \n", getpid());
				sleep(Tp);
			}
			break;
	}
	
	if (pid != 0) 
	{
		int stat_val;
		pid_t child_pid;
		child_pid = wait(&stat_val);
		printf("Child has finished: PID = %d\n", child_pid);
		if (WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}
	exit(exit_code);
}
