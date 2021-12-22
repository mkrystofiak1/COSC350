//Program: task1.c
//Author: Mitchell Krystofiak
//Description: Exam 2 COSC 350 Question 1
//Date: April 14, 2021

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int pipe1[2], pipe2[2];

	if (pipe(pipe1) < 0)
		printf("Could not open pipe1\n");
	if (pipe(pipe2) < 0)
		printf("Could not open pipe2\n");

	pid_t pid = fork();
	
	if (pid == 0) //child process
	{
		close(pipe1[0]); //read
		close(pipe2[1]); //write

		char message1[] = "Hi, Mom";

		write(pipe1[1], message1, 8);
		close(pipe1[0]);

		char buffer[11]; //message "i love you" == 11 bytes
		if (read(pipe2[0], buffer, 11) > 0)
		{
			printf("My mom said %s\n", buffer);
			close(pipe2[1]);
		}
	}
	else if (pid > 0) //parent process
	{
		close(pipe1[1]);
		close(pipe2[0]);
		
		char buffer[8]; //message "Hi, mom" == 8 bytes

		if (read(pipe1[0], buffer, 8) > 0)
		{
			printf("My child said %s\n", buffer);
			close(pipe1[0]);
		}

		char message2[] = "I love you\n";

		write (pipe2[1], message2, 11);
		close(pipe2[1]);
	}

	return 0;
}
