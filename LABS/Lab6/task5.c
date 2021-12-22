//Program: task5.c
//Author: Mitchell Krystofiak
//Description: File sharing between parent and child.
//Date: March 24, 2021

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
int is_digit(int c)
{
	if (c >= 48 && c <=57)
		return 1;
	else 
		return 0;
}

int main(int argc, char* argv[])
{
	pid_t pid;
	int infile, child, parent, exit_code, nread;
	char buffer;
	int childO = 0;
	int parentO = 0;
	
	if (argc != 2)
	{
		printf("Argument error!\n");
		exit(1);
	}

	if ((infile = open(argv[1], O_RDONLY)) < 0)
	{
		printf("Error opening input file!\n");
		exit(1);
	}

	parent = open("parent.txt", O_WRONLY | O_CREAT | O_EXCL, 0755);
	child = open("child.txt", O_WRONLY | O_CREAT | O_EXCL, 0755);
	
	if ( child < 0 || parent < 0)
	{
		printf("Output file error!\n");
		exit(1);
	}

	pid = fork();

	switch(pid)
	{
		case -1:
			perror("Fork failed.");
			exit(1);
		case 0:
			exit_code = 37;
			while ((pread(infile, &buffer, 1, childO)) == 1)
			{
				if (is_digit(buffer) == 0)
					write(child, &buffer, 1);
				childO++;
			}
			break;
		default:
			exit_code = 0;
			while((pread(infile, &buffer, 1, parentO)) == 1)
			{
				if (is_digit(buffer) == 1)
					write(parent, &buffer, 1);
				parentO++;
			}
			break;
	}
	close(infile);
	close(child);
	close(parent);

	if (pid != 0)
	{
		int stat_val;
        	pid_t child_pid;

        	child_pid = wait(&stat_val);

        	printf("Child  has finished: PID = %d. \n", child_pid);
        	if(WIFEXITED(stat_val))
        	{
            		printf("Child exited with code %d. \n", WEXITSTATUS(stat_val));
        	}
        	else
        	{
            		printf("Child terminated abnormally. \n");
        	}
    	}
    exit(exit_code);
}
