//Program: hello.c
//Author: Mitchell Krystofiak
//Description: Builds directory structures.
//Date: March 10, 2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	char home[] = "/home/mitchell";
	char location[256];
	chdir(home);

	sprintf(location, "%s/Dir1", home);
	mkdir(location, 0755);
	sprintf(location, "%s/Dir2", home);
	mkdir(location, 0755);
	sprintf(location, "%s/Dir21", location);
	mkdir(location, 0755);
	sprintf(location, "%s/hello", location);

	char a;
	int i, j;

	i = open("hello", O_RDONLY);
	j = open(location, O_CREAT | O_WRONLY, 0775);
	while(read(i, &a, 1) > 0)
		write(j, &a, 0);

	char locationLink[256];

	sprintf(location, "%s/Dir1/toDir21", home);
	sprintf(locationLink, "%s/Dir2/Dir21", home);

	symlink(location, locationLink);
	
	sprintf(location, "%s/Dir1/toHello", home);
	sprintf(locationLink, "%s/Dir2/Dir21/hello", home);

	symlink(location, locationLink);

	close(i);
	close(j);
	return 0;
}

