//Program: task3.c
//Author: Mitchell Krystofiak
//Description: This program will write message to file and then print out the message using different process.
//Date: March 31, 2021

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
	pid_t pid;
	int input, output;
	char buffer;

	//split processes
	pid = fork();

	if (pid < 0) //fork failure
	{
		printf("Fork failed.\n");
		exit(1);
	}
	
	


	else if (pid == 0) //child process
	{
		//Needs to write "Hi, mom" to foo, and then needs to end

		if((output = open("foo", O_WRONLY | O_CREAT | O_EXCL, 0755)) < 0)
		{
			printf("Output file error.\n");
			exit(1);
		}

		char message[] = "Hi, Mom.";

		write(output, &message, 8); //8 characters in message
	}
	else //parent process
	{
		//Needs to read foo and then say "My son said " then the message contained in foo in standard output

		wait(&pid); //wait for child to terminate
		
		if ((input = open("foo", O_RDONLY)) < 0)
		{
			printf("Input file error.\n");
			exit(1);
		}
		printf("My son said, ");

		 while (read(input, &buffer, 1) > 0) //reads byte by byte
		 	printf("%c", buffer);
	}
	printf("\n");
	close(input);
	close(output);
	
	exit(0);
}
