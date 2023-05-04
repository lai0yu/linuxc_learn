# 进程间通信

进程间通信，也称ipc 是interprocess-commnunition的简称，linux共有8种
进程通信的机制

[toc]

## 管道通信

### 匿名管道

我们知道fork出来的子进程，子进程复制了父进程的文件描述符表，但是却没有进行深度的拷贝，父子进程中两张文件描述符表的表项都指向了同一个文件总表节点。父子进程通过文件描述表的表项对一个文件进行读写操作的时候，其数据是共享的  
![file_d](https://pic2.imgdb.cn/item/645256da0d2dde57777428a2.jpg)

那么如果我们专门创建或者打开一个文件作为父子进程的信息交流使用，这种方式就叫做
匿名管道，

这种匿名管道实现的进程间通信有以下几个特点

1. 只能作用于父子进程通信
2. 由于是对同一个文件进行操作，只能一个进程读另一个进程写，如果两个进程同时写，就会造成数据混乱，通信异常，所以一个管道只能实现半双工，如果要实现同时双向交流，就得使用两个管道。
API

```c
#include <unistd.h>
int pipe(int pipefd[2]);
```

demo

```c
//no_name_pipe.c
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
```

编译并运行  
![no_name_pipe](https://pic2.imgdb.cn/item/645314220d2dde5777219fbb.jpg)

我们在命令行中使用的`|` 如 `ps -aux|grep usr` 本质上就是用无名管道实现的

### 有名管道

由于无名管道只能在父子进程中实现通信，linux提供了一个api创建有名管道用于通信

API

```c
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

demo mkfifo

```c
//mkfifow.c
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
    if (mkfifo_ret < 0) {`
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
```

```c
//mkfifor.c
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
```

编译并运行, 先在另一个终端运行mkfifow  
![mkfifo](https://pic2.imgdb.cn/item/64531e4c0d2dde57772d6e53.jpg)

### 高级管道

```c
#include <stdio.h>
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);
```

* popen()会调用fork()产生子进程，然后从子进程中调用/bin/sh -c来执行参数command的指令。
* 参数type可使用“r”代表读取，“w”代表写入。依照此type值，popen()会建立管道连到子进程的标准输出设备或标准输入设备，然后返回一个文件指针。
* 随后进程便可利用此文件指针来读取子进程的输出设备或是写入到子进程的标准输入设备中。此外，所有使用文件指针(FILE*)操作的函数也都可以使用，除了fclose()以外。

* 若成功则返回文件指针，否则返回NULL，错误原因存于errno中。

* 在编写具SUID/SGID权限的程序时请尽量避免使用popen()，popen()会继承环境变量，通过环境变量可能会造成系统安全的问题。

## 消息队列

## 信号量

## 信号

## 共享内存

## 套接字