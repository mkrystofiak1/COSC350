//Program: pipe4.c
//Author: Mitchell Krystofiak, BLP
//Description: Modify pipe4.c.
//Date: April 21, 2021

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int data_processed, data;
	char buffer[BUFSIZ + 1];
	int wFD, rFD;
	char message[] = "Hi Mom";

	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d", &rFD);
	sscanf(argv[2], "%d", &wFD);

	data_processed = read(rFD, buffer, BUFSIZ);
	data = write(wFD, message, 6);

	printf("Child %d recieved message \"%s\" of %d bytes. \n", getpid(), buffer, data_processed);
	printf("Child %d sent %d bytes to parent. \n", getpid(), data);
	exit(EXIT_SUCCESS);
}

