//Program: task2.c
//Author: Mitchell Krystofiak
//Date: April 28, 2021

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/msg.h>

typedef struct MSGBUF
{
        long type;
        int one;
        int two;
} MsgBuffer;

int main(int argc, char * argv[])
{
	key_t key;
	if ((key = ftok("msgQsnd.c", 'B')) == -1)
	{
		perror("ftok() error!");
		exit(1);
	}

	int Qid;
	if ((Qid = msgget(key, 0644 | IPC_CREAT)) == -1)
	{
		perror("msgget() error!");
		exit(1);
	}

	MsgBuffer buf;
	
	while (1)
	{
		if (msgrcv(Qid, (MsgBuffer *)&buf, 2 * sizeof(int), 0, 0) == -1)
		{
			perror("msgrcv() error\n");
			exit(1);
		}
		printf("The sum of the digits recieved from msgQsnd.c is %d \n", buf.one + buf.two);
	}

	return 0;
}
