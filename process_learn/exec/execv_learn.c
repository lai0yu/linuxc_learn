#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){

	printf("Current PID:%d\n",getpid());

	char* argv[] = {"ls","-l",NULL};

	int ret = execv("/bin/ls",argv);

	printf("This line will not be print after exec\n");

	return 0;
}
