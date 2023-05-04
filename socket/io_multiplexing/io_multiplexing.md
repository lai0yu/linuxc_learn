# IO多路复用

[toc]

## 概念

IO多路复用是一种用一个线程实现多个文件IO操作的同步IO模型，计算机中各个设备的信息传输都是通过IO实现的，比如磁盘IO，网络IO，

recv 只能对一个socket进行接收，在调用recv之前，无法知道客户端有没有发送新消息，当调用了recv之后才知道是否读取成功。

当一个服务器连接了多个客户端的时候，就要把多个客户端的发起的connect请求全部accept并保存这些客户端的socket，如果要服务端要能够同时接收所有客户端的发送的消息，那么只有两种方式，

1. 以阻塞的方式调用recv，一个客户端连接就开一个线程进行recv
2. 以非阻塞的方式调用recv, 使用一个线程循环recv每一个客户端
  
很明显，第二种方式优于第一种，服务器的性能有限，如果一个客户端连接就开一个线程，那么服务器压根不能承受这种开销。

如果要实现服务器接收消息的同时也能够接收新的连接，即recv的同时accept

但是accept没有找到好的非阻塞的方式，只找到[这篇文章](https://stackoverflow.com/questions/12861956/is-it-possible-and-safe-to-make-an-accepting-socket-non-blocking)，但个人认为非阻塞的accept不是特别正规的用法，所以还是单独开一个线程用来accept来实现

Demo1 多线程实现多端接收消息
```c
//multi_thread_server.c

```


### select

![](https://pic2.imgdb.cn/item/644b68b70d2dde5777f766d3.jpg=500x)

### poll

### epoll
