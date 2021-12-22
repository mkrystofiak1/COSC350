//Program: pipe3.c
//Authors: Mitchell Krystofiak, BLP
//Description: Modified pipe3.c.
//Date: April 21, 2021

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

const int READ_END = 0;
const int WRITE_END = 1;

int main()
{
	int data_processed, data;
	int file_pipes[2];
	int pipe2[2];
	const char message[] = "Hi there, Kiddo";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0 && pipe(pipe2) == 0)
	{
		fork_result = fork();
		if (fork_result == (pid_t)-1)
		{
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}

		if (fork_result == 0)
		{
			char readBuffer[BUFSIZ + 1];
			char writeBuffer[BUFSIZ + 1];
			close(file_pipes[1]);
			close(pipe2[0]);
			sprintf(readBuffer, "%d", file_pipes[0]);
			sprintf(writeBuffer, "%d", pipe2[1]);
			(void)execl("twoPipesChild", "twoPipesChild", readBuffer, writeBuffer, (char *)0);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(file_pipes[0]);
			close(pipe2[1]);
			data_processed = write(file_pipes[WRITE_END], message, strlen(message));
			data = read(pipe2[0], buffer, 6);
			printf("Parent %d sent %d bytes to the child .\n", getpid(), 15);
			wait(&fork_result);
			printf("Parent %d recieved the message \"%s\" of %d bytes\n", getpid(), buffer, data);
		}
	}
	exit(EXIT_SUCCESS);
}
