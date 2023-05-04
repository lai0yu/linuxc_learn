#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

void daemon_init();

int main(void) {
  daemon_init();
  openlog("测试守护进程", LOG_PID, LOG_DAEMON);
  int fd = open("xx.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    syslog(LOG_ERR, "测试日志");
    exit(-1);
  }

  char a[100] = "守护进程测试日志";
  while (1) {
    sleep(1);
    write(fd, a, strlen(a));
    syslog(LOG_INFO, "%s", a);
  }

  closelog();
  return 0;
}

void daemon_init() {
  // 1: 创建子进程
  if (fork() != 0) {
    exit(1);  // 退出父进程
  }
  // 2：给子进程为一个终端
  if (setsid() < 0) {
    perror("set sid error");
    exit(-1);
  }
  // 3:创建父进程
  if (fork() != 0) {
    exit(1);  // 退出子进程
  }

  // 4:关闭所有文件描述符
  int i;
  long j = sysconf(_SC_OPEN_MAX);
  for (i = 0; i <= j; i++) {
    close(i);
  }
  // 5:更换孙进程工作目录为根目录
  chdir("/");
  // 6:修改权限掩码，这样打开的文件和操作文件都有较高的权限
  umask(0);
  // 7:将标准输入输出错误重定向到NULL，彻底杜绝进程和终端的交互。
  int fd = open("dev/null", O_RDWR);
  dup(0);
  dup(0);
}
