#include <fcntl.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
	if (access("fifo_test", R_OK) == 0) {
		printf("fifo has been make\n");
	}else {

		int mkfifo_ret = mkfifo("fifo_test", 0666);
		if (mkfifo_ret < 0) {
			perror("mkfifo failed");
			return -1;
		}
	}

	char buf[512];

	int fd_r = open("fifo_test", O_CREAT|O_RDONLY,0666);

	if (fd_r > 0) {
		while (1) {
			bzero(buf, sizeof(buf));
			read(fd_r, buf, sizeof(buf));
			printf("recv message:%s\n",buf);
		}
	}
	close(fd_r);
	return 0;
}
