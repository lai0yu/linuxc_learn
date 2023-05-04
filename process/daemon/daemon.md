# 守护进程

守护进程是一类为了实现某种服务而特殊设计的进程

[toc]

## 特点

1. 一般以root权限运行，
2. 进程一般是1号进程(也称init进程)
3. 是非交互进程，不依赖没有控制终端，没有输出
4. 生存期长，一般在系统启动时运行，系统关闭时结束
5. 通常以`d`结尾，如`sshd` 、`crond`等

## 作用

最广泛的作用有如下两种

1. 系统级服务，如系统日志进程，
2. 各类网络应用服务器，如:
    * web服务器`httpd`
    * 邮件服务器`sendmail`
    * 数据库服务器`mysqld`

## 创建

守护进程和普通进程没有本质的区别，只是人为设计了一些特点，使用如下步骤就能构造一个守护进程

1. `fork()`出子进程，父进程使用`exit()`退出
2. 子进程调用`setsid()`创建新的会话
3. 再次`fork()`出孙进程，子进程调用exit退出
4. 孙进程调用`chadir('/')`，让根目录称为孙进程的工作目录
5. 孙进程调用umask，让孙进程的文件权限码为0
6. 孙进程调用dup，把标准输入、标准输出、标准错误输出重定向为NULL

## 管理

由于守护进程不受终端控制，所以一般用以下两种方式去管理

1. 使用系统日志来查看守护进程的信息
   由于守护进程的标注输入，标准输出，标准错误输出都被重定向为NULL了，所以自能利用系统日志来查看其中的信息，
  
    * 打开系统日志
  
      ```c
      #include <syslog.h>
      void openlog(
        const char *ident, 
        int option, //LOG_PID
        int facility //LOG_DAEMON
      );
      ```

    * 向系统日志写入
  

      ```c
      void syslog(
        int priority, //报文类型：LOG_ERR,LOG_WARNING,LOG_INFO 
        const char *format, //报文，参照printf的用法
        ...
      );
      ```

    * 关闭日志
    
      
      ```c
      closelog
      void closelog(void);
      ```

    * 查看日志:
      `sudo vim /var/log/syslog`

2. 使用`kill` 像守护进程发送信号

## Demo

```c
#include <sys/syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>

void daemon_init();

int main(void){
  daemon_init();
  openlog("测试守护进程", LOG_PID, LOG_DAEMON);
  int fd = open("xx.txt", O_RDWR|O_CREAT|O_TRUNC,0666);
  if (fd < 0) {
          syslog(LOG_ERR, "测试日志");
          exit(-1);
  }

  char a[100] = "守护进程测试日志";
  while (1) {
          sleep(1);
          write(fd, a, strlen(a));
          syslog(LOG_INFO, "%s",a);
  }

  closelog();
  return 0;
}

void daemon_init(){
  //1: 创建子进程
  if(fork()!=0){
          exit(1);//退出父进程
  }
  //2：给子进程为一个终端
  if (setsid()<0) {
          perror("set sid error");
          exit(-1);
  }
  //3:创建父进程
  if(fork()!=0){
          exit(1);//退出子进程
  }

  //4:关闭所有文件描述符
  int i;
  long j = sysconf(_SC_OPEN_MAX);
  for (i = 0; i <= j; i++) {
          close(i);
  }
  //5:更换孙进程工作目录为根目录
  chdir("/");
  //6:修改权限掩码，这样打开的文件和操作文件都有较高的权限
  umask(0);
  //7:将标准输入输出错误重定向到NULL，彻底杜绝进程和终端的交互。
  int fd = open("dev/null", O_RDWR);
  dup(0);
  dup(0);
}

```

编译并运行

```
gcc daemon_learn -o daemonlearnd
sudo ./daemonlearnd
```

使用`ps -aux`查看进程
![daemon_processlook](https://pic2.imgdb.cn/item/6452135e0d2dde57771e19e6.jpg)

使用`cat /xx.txt`查看守护进程输出的xx.txt文件
![daemon_output](https://pic2.imgdb.cn/item/645213a80d2dde57771e5c2e.jpg)

使用`sudo vi /var/log/syslog`查看日志输出
![daemon_test](https://pic2.imgdb.cn/item/64520e7f0d2dde5777175925.jpg)
