# Linux Socket 通信

[toc]

## 概念

Socket（套接字）是一种实现进程间通信的方式，与其他的IPC(interprocess-
commucation)方式相比有些特殊，Scoket不仅可以实现同一主机上的进程间通信，还可以实现不同主机进程间的通信。
![socket](https://pic2.imgdb.cn/item/644a3a0f0d2dde57779b4795.jpg=500x)

## 理解

为了实现互联互通的现代互联网，计算机网络定义了各种通讯协议，
每个计算机都需要实现这些协议才能接入互联网，这些协议统称为网络协议栈
为了让程序员能够在网络协议栈的基础上开发应用程序和服务，操作系统提供
Socket API，现在普及非常广的微信，QQ等即时通讯软件都直接或间接的使用
者套Socket API
![socket_is_api](https://pic2.imgdb.cn/item/644a320e0d2dde57778eefa6.jpg=500x)

## 使用

使用Socket通信共分以下几个步骤

创建套接字$\Rightarrow$绑定地址信息$\Rightarrow$连接$\Rightarrow$
收(发)数据$\Rightarrow$关闭套接字

![socket_use_step](https://pic2.imgdb.cn/item/644a3a620d2dde57779bbafb.jpg=500x)

### API

通信地址信息,一般我们使用`sockaddr_in`,它其实是`sockaddr`的另一种形式
可以相互转换

```c
struct sockaddr_in {
    short sin_family;              /* Address family */
    __be16    sin_port;            /* Port number */   
    struct in_addr sin_addr;       /* Internet address */
    unsigned char sin_zero[8];     /* Same size as struct sockaddr */
};
struct in_addr {
 unsigned long s_addr;  //IPv4
};

```

![](https://pic2.imgdb.cn/item/644a32c70d2dde5777900d81.jpg =500x)
`socket` 创建套接字

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
//说明：创建套接字
//参数：
//  domain：协议族，ipv4/ipv6
//  type：套接字类型 流式/数据报/原始
//  protocal：协议 tcp/udp
//返回值
//  成功返回套接字返回类型
//  失败返回-1，并设置错误码
```

`bind` 绑定地址信息

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int listen(int sockfd, int backlog);
//说明：套接字绑定进程地址
//参数
// sockfd：被监听的套接字描述符
// backlog：允许的最大连接数
//返回
// 成功返回0
// 失败返回-1，并设置错误码
```

`listen`启动监听，仅服务端需要

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int listen(int sockfd, int backlog);
//说明：监听
//参数
// sockfd：被监听的套接字描述符
// backlog：允许的最大连接数
//返回
// 成功返回0
// 失败返回-1，并设置错误码
```

`accept`服务端接收连接

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//说明：阻塞进程以等待一个接入入请求
//参数 
// sockfd：被请求接入者套接字
// sockaddr: 请求接入者地址
// addrlen： 请求接入者地址长度
//返回值
// 成功返回非负数整型值
// 失败返回-1
```

`connect`客户端请求连接

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//说明：请求连接
//参数
// sockfd： 请求接入者套接字
// addr：   被请求连接者地址
// addrlen：被请求接入者地址长度
//返回值
// 成功返回0
// 失败返回-1，并设置错误码
```

`send`发送数据

```c
#include <sys/types.h>
#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
//说明：发送数据
//参数: 
// sockfd: 发送对象
// buf:数据存放的地方
// len:buf的长度
// 阻塞
//返回值: 
// 成功返回发送的字节数
// 失败返回-1,并设置错误码
```

`recv`接收数据

```c
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
//说明：接收数据
//参数: 
//  sockfd:数据来源
//  buf:数据存放的地方
//  len:buf的长度
//  flags:0  阻塞    
//返回值: 
//  成功返回接收的字节数
//  失败返回-1,并设置错误码
// 如果断开连接返回0
```

### Demo

server.c

```c
#include <pthread.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
void* send_work(void* arg){
 char buf[40];
 while (1) {
  bzero(buf, sizeof(buf));
  scanf("%s",buf);
  send(*(int*)arg, buf, sizeof(buf), 0);
 }
}
void* recv_work(void* arg){
 char buf[40];
 int recv_ret = -1;
 while (1) {
  bzero(buf, sizeof(buf));
  recv_ret = recv(*(int*)arg, buf, sizeof(buf), 0);
  if(recv_ret > 0){
   printf("%s\n",buf);
  }

 }
}
int main(int argc, char* argv[]){
 if (argc < 3) {
  printf("Usage:%s <IP> <Port>\n",argv[0]);
  return -1;
 }
 int serv_sock = socket(AF_INET, SOCK_STREAM,IPPROTO_IP);
 struct sockaddr_in serv_addr;
 memset(&serv_addr, 0, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
 serv_addr.sin_port = htons(atoi(argv[2]));
 if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
  perror("bind error");
  return -1;
 } 

 listen(serv_sock,40);
 struct sockaddr_in cli_addr;
 socklen_t cli_addr_len = sizeof(cli_addr);
 int cli_sock = accept(serv_sock, (struct sockaddr*)&cli_addr,&cli_addr_len);
 printf("Client %d has connected\n",cli_sock);

 pthread_t recv_thread;
 pthread_create(&recv_thread, NULL, recv_work,&cli_sock);
 pthread_detach(recv_thread);

 send_work(&cli_sock);
 return 0;
}
```

client.c

```c

#include <pthread.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
void* recv_work(void *arg){
 char buf[40];
 int recv_ret = -1;
 while(1){
  bzero(buf, sizeof(buf));
  int recv_ret = recv(*(int*)(arg), buf, sizeof(buf), 0);
  if (recv_ret > 0) {
   printf("%s\n",buf);
  }
 }
}
void* send_work(void *arg){
 char buf[40];
 while (1) {
  bzero(buf, sizeof(buf));
  scanf("%s",buf);
  send(*(int*)(arg), buf, sizeof(buf), 0);
 }
}
int main(int argc, char* argv[]){
 if (argc < 3) {
  printf("Usage:%s <IP> <Port>\n",argv[0]);
  return -1;
 }
 int self_sock = socket(AF_INET, SOCK_STREAM,IPPROTO_IP);

 struct sockaddr_in serv_sock_addr;
 serv_sock_addr.sin_family = AF_INET;
 serv_sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
 serv_sock_addr.sin_port = htons(atoi(argv[2]));
 int connect_ret =connect(self_sock, (struct sockaddr*)&serv_sock_addr, sizeof(serv_sock_addr));
 if(connect_ret < 0){
  perror("connect error");
  return -1;
 }

 pthread_t recv_thread;
 pthread_create(&recv_thread, NULL, recv_work, &self_sock);
 pthread_detach(recv_thread);

 send_work(&self_sock);
 return 0;
}
```

编译：

```shell
gcc server.c -pthread -o server
gcc client.c -pthread -o client
```

结果  
![server_run_result](https://pic2.imgdb.cn/item/644a34180d2dde5777922b5e.jpg)
![client_run_result](https://pic2.imgdb.cn/item/644a33e20d2dde577791d73e.jpg)
