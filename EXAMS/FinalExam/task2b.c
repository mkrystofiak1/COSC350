//Program: task2b.c
//Author: Mitchell Krystofiak
//Date: May 7, 2021

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>
#include"header.h"
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>

typedef struct MSGBUF
{
	long type;
	int one;
	int two;
} MsgBuffer;

int main(int argc, char *argv[])
{
	key_t key;
	struct Memory *shm;
	key = ftok(".", 'B');	
	int QID;
	if ((QID = msgget(key, 0644)) == -1)
	{
		perror("msgget() error!\n");
		exit(1);
	}

	int shmid;
	key_t key2;
	key2 = ftok(".", 'B');

	if ((shmid = shmget(key2, sizeof(struct Memory), IPC_CREAT | 0666)) < 0)
	{
		perror("shmget() error!\n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if ((long)shm == -1)
	{
		perror("shmget() error!\n");
		exit(1);
	}
	MsgBuffer buf;
	shm->status = NOT_READY;
	shm->gostop = GO;

	for (; ;)
	{
		if (msgrcv(QID, (struct MsgBuffer *)&buf, sizeof(buf), 0, 0) == -1)
		{
			shm->gostop = STOP;
			shm->status = STOP;
			shmdt((void *) shm);
		}
		printf("Sending over data to task2c.c\n");
		shm->data.value1 = buf.one;
		shm->data.value2 = buf.two;
		shm->status = FILLED;
		while (shm->status != TAKEN)
			;
	}
        return 0;
}
