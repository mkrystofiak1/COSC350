//Program: mygetenv.c
//Author: Mitchell Krystofiak
//Description: A getenv() function.
//Date: March 24, 2021

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

extern char** environ;

char* mygetenv(char* n)
{
	int nlen = strlen(n);
	for (int i = 0; environ[i] != '\0'; i++) //scans the list of environment variables
	{
		int j = 0;
		while (environ[i][j] != '\0')
		{
			if (j > nlen && environ[i][j] == '=')
				break;
			else if (nlen == j && environ[i][j] == '=')
				return environ[i];
			else if (n[j] != environ[i][j])
				break;
			else
				j++;
		}
	}
}

int main(int argc, char * argv[])
{
	/*if (argc != 2)
	{
		printf("ERROR: Expecting 1 arguments!\n");
		return 1;
		*/

	printf("Using mygetenv, %s\n", mygetenv("HOME"));
	printf("Using mygetenv, %s\n\n", mygetenv("PATH"));
	printf("Using regular getenv, HOME=%s\n", getenv("HOME"));
	printf("Using regular getenv, PATH=%s\n\n", getenv("PATH"));
	
	printf("Using mygetenv, %s\n", mygetenv(argv[1]));
	return 0;
}
