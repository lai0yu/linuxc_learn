#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    printf("I am sub process 1; my PID is %d\n", getpid());
    sleep(3);
    exit(1);
  }
  int wstatus, ret;
  ret = wait(&wstatus);
  printf("被回收的子进程是：%d\n", ret);
  printf("被回收的子进程死亡状态是:%d\n", wstatus);

  while (1) {
  }

  return 0;
}
