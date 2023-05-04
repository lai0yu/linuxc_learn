// process_lock1.c
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("test.c", O_RDWR | O_APPEND);
  if (fd < 0) {
    perror("open error\n");
    return -1;
  }

  char buf[30] = "唱跳rap篮球\n";
  while (1) {
    sleep(1);
    flock(fd, LOCK_EX);
    printf("唱锁\n");
    sleep(3);
    write(fd, buf, strlen(buf));
    printf("%s\n", buf);

    sleep(50);
    printf("解唱锁\n");
    flock(fd, LOCK_UN);
    printf("解锁成功\n");
  }
  return 0;
}
