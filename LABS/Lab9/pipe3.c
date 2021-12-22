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
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0)
	{
		fork_result = fork();
		if (fork_result == (pid_t)-1)
		{
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}

		if (fork_result == 0)
		{
			char writeBuffer[BUFSIZ + 1];
			sprintf(buffer, "%d", file_pipes[0]);
			sprintf(writeBuffer, "%d", file_pipes[1]);
			(void)execl("pipe4", "pipe4", buffer, (char *)0);
			exit(EXIT_FAILURE);
		}
		else
		{
			data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
			close(file_pipes[1]);
			wait(&fork_result);
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
