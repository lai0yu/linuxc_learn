#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	//制作收尸程序,父进程给子进程收尸
	pid_t pid=fork();//开展子进程 
	if(pid==0){
		//子进程的操作
		printf("我是子进程1  我的PID号为:%d\n",getpid());
		sleep(3);
		exit(100);//让子进程死亡,完成收尸,让操作停留在这里
	}
	pid_t pid2=fork();
	if(pid2==0){
		//子进程的操作
		printf("我是子进程2  我的PID号为:%d\n",getpid());
		printf("老二当前的组号为:%d\n",getpgid(pid2));
		printf("我!是!二!五!仔!\n");
		setpgid(pid2,pid2);//老二单独成组
		printf("老二叛变后的组号为:%d\n",getpgid(pid2));
		sleep(4);
		exit(2);//让子进程死亡,完成收尸,让操作停留在这里
	}
	pid_t pid3=fork();
	if(pid3==0){
		//子进程的操作
		printf("我是子进程3  我的PID号为:%d\n",getpid());
		sleep(5);
		exit(3);//让子进程死亡,完成收尸,让操作停留在这里
	}
	//父进程的操作
	//sleep(3);
	int wstatus,ret;
	//ret=waitpid(pid2,&wstatus,0);//给特定子进程收尸
	
	
	//给和父进程同一进程组下的子进程收尸
	/*while(1){
	ret=waitpid(0,&wstatus,0);
	if(ret==-1){
		break;
	}
	printf("被收尸的子进程是:%d\n",ret);
	}*/
	
	
	
	//给任意子进程收尸,无论同不同组
	/*while(1){
	ret=waitpid(-1,&wstatus,0);
	if(ret==-1){
		break;
	}
	printf("被收尸的子进程是:%d\n",ret);
	}*/
	
	
	
	//给进程组|pid|下的子进程收尸
	/*sleep(4);
	while(1){
	ret=waitpid(-pid2,&wstatus,0);
	if(ret==-1){
		break;
		}
	printf("被收尸的子进程是:%d\n",ret);
	}*/
	
	
	//死因追查
	sleep(2);
	waitpid(-1,&wstatus,WUNTRACED);
	if(WIFEXITED(wstatus)){//子进程是否正常死亡?
		printf("死亡原因:正常死亡,死亡状态为:%d\n",WEXITSTATUS(wstatus));
	}
	if(WIFSIGNALED(wstatus)){//子进程是否被信号停止或杀死
		printf("死亡原因:被信号%d杀死\n",WTERMSIG(wstatus));
	}
	if(WIFSTOPPED(wstatus)){//子进程是否被信号暂停
		printf("死亡原因:被信号%d暂停\n",WSTOPSIG(wstatus));
	}
	return 0;
}
