//Program: msgQsnd.c
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
		perror("ftok() error!\n");
		exit(1);
	}

	int Qid;
	if ((Qid = msgget(key, 0644 | IPC_CREAT)) == -1)
	{
		perror("msgget() error!\n");
		exit(1);
	}

	MsgBuffer buf;
	buf.type = 1;
	char * input = (char *)calloc(256, sizeof(int));

	puts("Enter two integer values: ");

	while(fgets(input, 256, stdin), !feof(stdin))
	{
		sscanf(input, "%d%d", &buf.one, &buf.two);
		if (msgsnd(Qid, (MsgBuffer *)&buf, 2 * sizeof(int), 0) == -1)
			perror("msgsnd() error!\n");

		puts("Enter two integer values: ");
	}

	if (msgctl(Qid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl() error!\n");
		exit(1);
	}
	return 0;
}
