//Program: child.c
//Authors: reference.pdf; Mitchell Krystofiak (edit)
//Desciption: A separate program to function like forkWait.c
//Date: March 24, 2021

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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
	int Nc = str_to_int(argv[0]);
	int Tc = str_to_int(argv[1]);

	for(; Nc > 0; Nc--)
	{
		printf("Child PID = %d \t %s \n", getpid(), argv[2]);
		sleep(Tc);
	}
	exit(37);
}
