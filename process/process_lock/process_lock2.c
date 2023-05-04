#include <string.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
	int fd = open("test.c", O_RDWR | O_APPEND);
	if (fd < 0)
	{
		perror("open error");
		return -1;
	}

	char buf[30] = "鸡你太美\n";

	while (1)
	{
		sleep(1);
		flock(fd, LOCK_EX);
		printf("鸡锁\n");

		sleep(3);
		write(fd, buf, strlen(buf));
		printf("%s\n", buf);

		printf("解鸡锁\n");
		flock(fd, LOCK_UN);
		printf("解锁成功\n");
	}

	return 0;
}
