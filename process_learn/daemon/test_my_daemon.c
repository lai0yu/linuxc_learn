#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>
#include "my_deamon.h"
int main(){
	deamon_init();

	openlog("",LOG_PID,LOG_DAEMON);

	int fd = open("xx.txt", O_RDWR);

	if(fd < 0){
		syslog(LOG_ERR,"tkl");
		exit(-1);
	}

	char a[100] ="梦想当说唱两袖\n";

	while(1){
		sleep(1);
		write(fd,a,strlen(a));
		syslog(LOG_INFO,"%s",a);
	}
	closelog();
	return 0;
}
