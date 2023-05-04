// fock.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	// 父子进程，空间独立，一份程序, 两处运行, 在fork下面的所有语句会被父子两个进程运行
	pid_t son_pid = fork();

	printf("Hello World pid:%d\n", son_pid);

	while (1)
	{
	}

	return 0;
}
