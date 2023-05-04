#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
int main(void)
{

	key_t key = ftok("1.c", 1);
	if (key < 0)
	{
		perror("ftok key error\n");
		return -1;
	}
	printf("key:%#x\n", key);

	int shmid = shmget(key, 200, IPC_CREAT | 0666);
	return 0;
}
