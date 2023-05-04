#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
	if (access("fifo_test", W_OK) == 0){
		printf("fifo has been make\n");
	}else {
		int mkfifo_ret = mkfifo("fifo_test", 0666);
		if (mkfifo_ret < 0) {

			perror("mkfifo failed");
			return -1;
		}
	}	

	char* message = "嘀嘀嘀";

	int fd_w = open("fifo_test", O_CREAT|O_WRONLY,0666);

	if (fd_w > 0) {
		while (1) {
			write(fd_w, message, strlen(message));
			sleep(1);
		}
	}
	close(fd_w);
	return 0;
}
