//Program: pipe1.c
//Authors: Mitchell Krystofiak, BLP
//Description: Modify pipe1.c.
//Date: April 21, 2021

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int READ_END = 0;
const int WRITE_END = 1;

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char* buffer = malloc(3 * sizeof(char));
	memset(buffer, '\0', 3);

	if (pipe(file_pipes) == 0)
	{
		data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
		//data_processed = read(file_pipes[0], buffer, BUFSIZ);
		printf("Wrote %d bytes\n", data_processed);
		data_processed = read(file_pipes[READ_END], buffer, 3);
		//data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("Read %d bytes: %s\n", data_processed, buffer);
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	free(buffer);
	exit(EXIT_FAILURE);
}
