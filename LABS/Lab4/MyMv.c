//Program: MyMv
//Author: Mitchell Krystofiak
//Description: Write a mv function.
//Date: March 10, 2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	umask(0);

	if (argc != 3) //check for arguments (file name and path to new directory)
	{
		printf("Error! Expecting 3 arguments!\n");
		return 1;
	}

	struct stat dir;
	stat(argv[2], &dir);

	if (S_ISDIR(dir.st_mode)) //if moving to an already created directory
	{
		char path[strlen(argv[2]) + strlen(argv[1])];
		sprintf(path, "%s", argv[2]);
		sprintf(path, "%s/%s", path, argv[1]);
		link(argv[1], path);
		unlink(argv[1]);
	}

	return 0;
}

