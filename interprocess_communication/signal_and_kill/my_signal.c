#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void father_handler(){
	printf("father%d:鸡哥很帅\n",getpid());
	kill(getpid() + 1, SIGINT);
	sleep(2);
}
void son_handler(){
	printf("son%d:那他会唱欧恩调么\n",getpid());
	kill(getppid(),SIGUSR1);
	sleep(2);
}


int main(void){

	int fork_ret= fork();
	if(fork_ret > 0){
		if(signal(SIGUSR1,father_handler) != SIG_ERR){
			printf("father%d: i has register signal\n",getpid());
		}
	}else{
		if(signal(SIGINT,son_handler) != SIG_ERR){
			printf("son:%d: i has got signal\n",getpid());
			kill(getppid(), SIGUSR1);
		}
	}

	while(1){
	}

	return 0;
}
