//Program: fork1.c
//Authors: reference.pdf; Mitchell Krystofiak (edit)
//Desciption: Edited fork1 to take in line arguments.
//Date: March 24, 2021

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int str_to_int(char * ch)
{
	int x = 0;
	int number = 0;
	while (ch[x] != '\0')
	{
		number = 10 * number + (ch[x] - '0');
		x++;
	}
	return number;
}

int main(int argc, char * argv[])
{
	if ( argc != 5 ) //five arguments
	{
		printf("Error: Expecting 4 inputs!\n");
		exit(1);
	}

	pid_t pid;
	char *message;
	int Nc = str_to_int(argv[1]);
	int Np = str_to_int(argv[2]);
	int Tc = str_to_int(argv[3]);
	int Tp = str_to_int(argv[4]);
	int slp;
	printf("%d", Nc);
	
	int n;
	printf("fork program starting\n");
	pid = fork();
	switch(pid) 
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			n = Nc;
			slp = Tc;
			break;
		default:
			message = "This is the parent";
			n = Np;
			slp = Tp;
			break;
	}
	for(; n > 0; n--) 
	{
		puts(message);
		sleep(slp);
	}
	exit(0);
}
