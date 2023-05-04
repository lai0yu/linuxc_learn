#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* thread1_work(void* arg){
	printf("thread1:I am working, arg is:%s \n",(char*)arg);
	sleep(3);
	pthread_exit("this is my(thread1) exit word");	
}

int main(void){
	pthread_t thread1;
	char *arg = "thread1 work arg";
	pthread_create(&thread1, NULL, thread1_work, arg);
	char** retval;
	printf("have you finished?,i am waitting\n");
	pthread_join(thread1, (void**)retval);
	printf("thread1 exit return:%s\n",*retval);
	return 0;
}
