//Program: task3.c
//Author: Mitchell Krystofiak
//Date: May 7, 2021

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int sig)
{
	//manage signal between parent and child
	if (sig == SIGUSR1)
	{
	}
}

int main()
{
	int status;
	int p[2];

	pipe(p);

	int fd1 = open("foo", O_CREAT | O_RDWR, 0666);
	int fd2 = dup(fd1);

	pid_t pid = fork();
	signal(SIGUSR1, handler);
	
	if (pid == 0) //child process
	{
		write(fd2, "Hi, Mom", 7);
		close(fd2);
		kill(getppid(), SIGUSR1);
		pause();

		close(p[1]);
		char message[18];
		if (read(p[0], message, 18) > 0)
		{
			printf("My Mom said %s\n", message);
			close(p[0]);
		}

		return 0;
	}

	else //parent process
	{
		pause();
		lseek(fd1, SEEK_SET, 0);
		char msg[7];
		read(fd1, msg, 7);
		printf("My son said %s\n", msg);
		close(fd1);

		char buffer[18] = "What do you want\0";
		write(p[1], buffer, 18);
		kill(pid, SIGUSR1);

		close(p[1]);
	}

	return 0;
}


