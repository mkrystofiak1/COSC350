//Program: task4.c
//Author: Mitchell Krystofiak
//Description: Interprocess communication using popen() and pclose().
//Date: April 7, 2021

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("Argument error!\n");
		exit(1);
	}
	int i;
	int size = 0;
	char *command;

	for (i = 1; i < argc; i++)
		size += strlen(argv[i]);

	command = calloc(size, sizeof(char));

	for (i =1; i < argc; i++)
		sprintf(command, "%s %s", command, argv[i]);

	char buffer[BUFSIZ];
	FILE *ptr;

	if ((ptr = popen(command, "r")) != 0)
	{
		while (fgets(buffer, BUFSIZ, ptr) != 0)
			(void) printf("%s", buffer);
	}
	pclose(ptr);

	return 0;
}
