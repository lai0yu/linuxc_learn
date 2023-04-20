#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("User:%s <read_filename> <write_filename>\n",argv[0]);
		return -1;
	}
	int fd_r = open(argv[1], O_RDONLY);
	int fd_w = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(fd_r < 0 || fd_w < 0){
		printf("File Open failed!\n");
		return -1;
	}
	
	int ret;
	char buf[256]  = {0};
	while(1){
		bzero(buf,sizeof(buf));
		ret = read(fd_r,buf,sizeof(buf));
		if(ret <= 0){
			printf("finish copy\n");
			break;
		}
		write(fd_w,buf,strlen(buf));
	}
	close(fd_r);
	close(fd_w);
	return 0;
}
