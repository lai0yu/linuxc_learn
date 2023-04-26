#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void *show1(void* arg){
	while (1) {
		sleep(2);
		printf("thread:i am run in a thread\n");
		printf("args:%s\n",(char*)arg);
	}
}

void *show2 (void * arg){
	while(1){
		sleep(2);
		printf("thread:i am run in another thread\n");
		printf("args:%s\n",(char*)arg);
	}
}

int main(){
	pthread_t thread1;
    char str1[30] = "thread 1 args";
	pthread_create(&thread1,NULL,show1,str1);
    
	pthread_t thread2;
	char str2[30] = "thread 2 args";
	pthread_create(&thread2, NULL, show2, str2);

	while(1);

	return 0;
}
