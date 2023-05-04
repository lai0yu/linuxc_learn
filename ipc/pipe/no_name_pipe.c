#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
int main(void){
	int pipe_fd[2] = {-1,-1};
	//两个文件描述符定义一个管道，一个文件描述符用来读，另一个用来写。
	if (pipe(pipe_fd)<0) {
		perror("new pipe errorn");
		return -1;
	}

	pid_t pid = fork();
	if (pid == 0) {
		//child process
		
		close(pipe_fd[0]);//pipe_fd[0]是读，这里子进程发消息给父进程,子进程不用读操作，
		char* child_message = "嘀嘀嘀\n";
 		while (1) {
			write(pipe_fd[1], child_message, strlen(child_message));
			sleep(1);
		}

	}else {
		//father process
		close(pipe_fd[1]);//父进程用不到写操作
		char buf[512];
		size_t read_ret;
		while (1) {
			bzero(buf, sizeof(buf));
			read_ret = read(pipe_fd[0], buf, sizeof(buf)-1);
			if (read_ret > 0) {
				printf("father recv from child:%s\n",buf);
			}
		}
	}
	return 0;
}
