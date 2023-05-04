#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* thread_work(void* arg){
	printf("I am working, args is :%s \n",(char*)arg);
	char* dead_word = "I hava to exit my work";
	pthread_exit(dead_word);
	printf("finish work\n");
}

int main(void){
	pthread_t thread1;
	char * arg = "give thread1 arg";
	pthread_create(&thread1, NULL, thread_work, arg);
	sleep(1);
	return 0;
}
