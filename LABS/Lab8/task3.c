//Program: task3.c
//Author: Mitchell Krystofiak
//Description: Interprocess communication using pipe.
//Date: April 7, 2021

#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256

int main()
{
	int n, size, num1, num2;
	int fd[2];
	pid_t pid;
	char sline[MAXLINE], rline[MAXLINE];

	if (pipe(fd) < 0){
		puts("Pipe error.");
		exit(1);
	}

	if ((pid = fork()) < 0){
		puts("Fork failed.");
		exit(1);
	}
	else if (pid > 0)
	{
		close(fd[0]);

		puts("Please enter two integers.");

		while((size = read(STDIN_FILENO, sline, MAXLINE)) > 0)
		{
			write(fd[1], sline, size);

			puts("Enter two more integers.");
		}
	}
    else
	{
		close(fd[1]);

		while((n = read(fd[0], rline, MAXLINE))>0)
		{
			if(sscanf(rline, "%d%d", &num1, &num2) == 2)
			{
				sprintf(rline, "The sum is %d\n", num1 + num2);

				n = strlen(rline);

				if (write(STDOUT_FILENO, rline, n) != n){
					puts("Writing error.");
					exit(1);
				}
			}
			else
			{
				if (write(STDOUT_FILENO, "Invalid input. Must enter two integers.\n", 40) != 40){
					puts("Writing error");
					exit(1);
				}
			}
		}
	}
	return 0;
}
