# 进程的生命周期

![process_life](https://pic2.imgdb.cn/item/644e26320d2dde5777dd9940.jpg)

[toc]

## 创建

linux提供了如下三个api创建一个新的进程

### 1.`fork`

```c
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
//说明：创建一个子进程，
//返回：子进程pid，
```

fork创建了一个新的task_struct和pid， 但其他所有资源都是复制父进程的，这些资源包括，堆栈空间以及堆栈空间的变量  

![fork_copy](https://pic2.imgdb.cn/item/644e2c240d2dde5777e55981.jpg)

在fork之后，子进程和父进程都会继续执行fork调用之后的指令  
由于这样特性fork调用一次，有两个返回，分别在子进程和父进程，子进程返回0，父进程返回子进程的pid
fork出来子进程相对于父进程是独立的进程，其执行顺序由内核调度决定，所以到底是父进程先执行还是子进程先执行并不确定

Demo

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
  //父子进程，空间独立，一份程序, 两处运行, 在fork下面的所有语句会被父子两个进程运行
  pid_t son_pid = fork();

  printf("Hello World pid:%d\n",son_pid);

  while (1) {}
  return 0;
}

```

编译并运行
![fork_learn](https://pic2.imgdb.cn/item/64521b2c0d2dde5777255de8.jpg)

### 2.`vfork`

vfork也是创建一个新的子进程，父进程调用vfork之后，父进程会立即阻塞，知道子进程调用`exec()`或者`exit`。所以保证了子进程先执行。

fork 和 vfork 的区别

1. fork：子进程拷贝父进程的数据段和代码段内存，父子相互独立，
   vfork：子进程直接使用父进程的数据段和代码段
2. fork：父子进程一起执行，次序不确定
   vfork：子进程先执行，在子进程调用exit或exec后，父进程才会运行

要注意的点

1. vfork的子进程由于完全是在父进程的内存上运行的，所以子进程运行造成某个变量的修改会影响到父进程，
2. 调用vfork之后，父进程进入阻塞状态，如果子进程依赖父进程的下一步结果，就会造程死锁

由于早年linux没有实现cow(copy on write，写时拷贝)技术，为了提升进程复制效率，提供这样一个函数，现在这个函数已经不具优势了，用的比较少。

### 3.`clone`

```c
/*
*功能：创建新的进程。
*@__fn:进程函数指针。
*@__child_stack:进程的栈空间。
*@__flags:新进程选择性拷贝老进程的标志。
*@__arg:老进程要给新进程传递的参数。
*@retval:
*    1.进程创建失败，返回-1，错误见errno
*    2.进程创建成功，返回新进程的PID(>0)
*/
int clone(int (*__fn)(void *__arg),
                 void *__child_stack,
                 int __flags,
                 void *__arg, ...);
```

clone函数不是posix接口，不可以跨平台使用

clone函数功能强大，参数较多，使用较为复杂

clone函数的本质不再局限于创建子进程，而是克隆，它可以指定新克隆出来的进程和原进程的关系是兄弟关系

## 替换

通过fork 函数创建的子进程都是父进程的拷贝，那么执行新的程序肯定是要运行完全不同的进程，这个时候就需要使用exec函数簇来替换掉fork出来的子进程

### API

exec函数簇本质都是由execve实现的，他们调用关系大致如下
![exec](https://pic2.imgdb.cn/item/644e454d0d2dde577700354c.jpg=500x)

```c
#include <unistd.h>
extern char **environ;
int execl(const char *path, const char *arg, .../* (char  *) NULL */);
int execlp(const char *file, const char *arg, .../* (char  *) NULL */);
int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],char *const envp[]);
```

实际上exec后面带l、v、p、e分别表示不同的含义

可以相互组合，有以下两种组合方式

1. 带l: (即list)表示以参数列表的形式声明新程序执行参数
     - 带p: (即path)表示使用 filename 做参数，如果 filename 中包含“/”，则视为路径名，否则在 PATH 环境变量所指定的各个目录中搜索可执行文件
     - 带e:(即environment)表示可以传递一个指向环境字符串指针数组的指针，环境数组需要以 NULL 结束
2. 带v: (即vector)表示以数组的方式声明新程序执行参数
    - 带p: (即path)表示使用 filename 做参数，如果 filename 中包含“/”，则视为路径名，否则在 PATH 环境变量所指定的各个目录中搜索可执行文件
    - 带e: (即environment)表示可以传递一个指向环境字符串指针数组的指针，环境数组需要以 NULL 结束

### Demo

先制作一个新的程序 new

```c
//new.c
#include <stdio.h>
int main(int argc, char *argv[]){
  extern char** environ;
  printf("new process run\n");
  return 0;
}
```

#### 1.demo execl

```c
//execl_learn.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  printf("Current PID:%d\n",getpid());

  int ret = execl("./new", "./new",NULL);
  //第一个./new--->在exec.c的执行目录下寻找一个名为new的可执行文件
  //第二个./new--->执行 名为  new 的可执行文件，是替换后进程main函数的第一个参数
  //NULL 表示后面没有参数了，比如要传入一个参数arg1，execl("./new","./new",arg1,NULL),相当于参数列表停止标志。
  printf("被替换后不会打印这一行");
  return 0;
}

```

编译并运行  
![execl](https://pic2.imgdb.cn/item/645245050d2dde57775b5c93.jpg)

#### 2.demo execlp

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
  printf("Current Pid:%d\n",getpid());
  int ret = execlp("ls","ls","-a",NULL);
  //第一个ls  :在默认/bin  和 /usr/bin 寻找一个名为ls的命令
  //第二个ls  :执行ls 
  //第三个-l  :执行ls命令下 -l 选项,显示文件详细信息
  printf("被替换后不会再打印这一行\n");
  return 0;
}
```

编译并运行  
![execlp](https://pic2.imgdb.cn/item/645245d10d2dde57775c7fec.jpg)

#### 3.demo execv

```c
//execv.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
  printf("Current PID:%d\n",getpid());
  char* argv[] = {"ls","-l",NULL};
  int ret = execv("/bin/ls",argv);
  printf("This line will not be print after exec\n");
  return 0;
}
```

编译并运行  
![execv](https://pic2.imgdb.cn/item/645246b90d2dde57775df32b.jpg)

#### 4.demo execvpe

```c
//execvpe_learn.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){
        printf("Current PID:%d\n",getpid());
        char* argv[] = {"./new",NULL};
        char* envp[] = {"AA","BB","CC","DD",NULL};
        int ret = execvpe("./new",argv,envp);
        printf("This line will not been print after exec\n");
        return 0;
}
```

分别编译
![ec](https://pic2.imgdb.cn/item/645243bb0d2dde577759a5c7.jpg)

定义一个临时的环境变量
![env](https://pic2.imgdb.cn/item/645243530d2dde5777592fe4.jpg)

运行结果  
![re](https://pic2.imgdb.cn/item/645244390d2dde57775a4e4a.jpg)

## 就绪

进程已经获得除时间片以外的所有所需资源，等待cpu分配时间片运行

## 运行

当一个进程在处理机上运行时，则称该进程处于运行状态

## 阻塞或挂起

区别和联系

1. 阻塞和挂起状态的进程都不占用cpu时间片，
2. 阻塞的进程仍然保留再内存中，挂起的进程被交换到外存中(磁盘)

### 1.阻塞

当进程所需要的资源还未就绪时，再让该进程占着cpu时间片就不合适了，这个时候系统会让进程进入的阻塞状态，释放时间片。

进程被阻塞的原因有很多种，但是等待资源是最常见的原因，这些原因通常会导致进程就算占着cpu时间片也无法运行，所以系统就会把cpu时间片释放出来分配给别的进程

### 2.挂起

挂起状态：由于IO的速度慢于CPU的运算速度，经常出现CPU等待I/O的情况。这时OS需要将主存中的进程对换至外存。在进程行为模式中需要增加一个新的挂起（suspend）状态。当内存中所有进程阻塞时，OS可将一进程置为挂起态并交换到外存，再调入另一个进程执行。

## 死亡

### 正常死亡

1. main函数返回
  
2. 调用exit或_exit
exit和_exit的区别在于:exit在结束进程之前,会刷新输入输出缓冲区，

### 非正常死亡

1. 调用abort

2. 接收到kill信号，比如我们使用Ctrl+C结束当前进程，实际上是发送用kill发送了一个SIGINT信号来终止进程。

## 回收

当一个进程退出之后，进程能够回收自己的用户区的资源，但是不能回收内核空间的PCB资源，必须由它的父进程调用wait或者waitpid函数完成对子进程的回收，避免造成系统资源的浪费。

但是父进程和子进程时相互独立的进程，有独立的生命周期，如果子进程还存活，父进程就已经死亡了呢，这样的进程称为孤儿进程，为了防止系统资源被浪费，孤儿进程会被0号进程自动领养，并最终由0号进程回收。

子进程已经死亡，但是父进程没有成功回收这个已经死亡的子进程，这个进程称为僵尸进程，由于子进程已经死亡，所以无法用kill去解决它，解决僵尸进程的方法只有杀死它的父进程，让僵尸进程称为孤儿进程，由0号进程进行回收。

linux系统提供`wait`和`waitpid`两个函数来进行回收

并且使用如下宏判断子进程死亡原因

1. WIFEXITED(status)判断子进程是否正常结束（正常结束则返回逻辑真，否则返回逻辑假）
2. WEXITSTATUS(status)如果子进程是正常结束，获取子进程返回值（即通过exit/_exit/return返回的值）
3. WIFSIGNALED(status)判断子进程是否被信号结束（即判断子进程是否非正常结束）
4. WTERMSIG(status)如果子进程非正常结束，获取结束子进程的信号类型

### 1.`wait`

![wait_guide](https://pic2.imgdb.cn/item/644e68820d2dde577725e765.jpg)

如果调用wait之前，该进程就已经有两个及以上的需要回收的子进程，wait会随机选取一个子进程进行回收，没有明确的先后顺序，这个其实和pcb的组织和进程调度有关，无需深究

demo
```c
//wait.c
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  pid_t pid = fork();
  if(pid == 0){
          printf("I am sub process 1; my PID is %d\n", getpid());
          sleep(3);
          exit(1);
  }
  int wstatus,ret;
  ret = wait(&wstatus);
  printf("被回收的子进程是：%d\n",ret);
  printf("被回收的子进程死亡状态是:%d\n",wstatus);

  while(1){}
  return 0;
}
```

编译并运行  
![wait](https://pic2.imgdb.cn/item/64524b000d2dde57776515eb.jpg)

### 2.`waitpid`

![waitpid_guide](https://pic2.imgdb.cn/item/644e68a80d2dde5777260ada.jpg)

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
 //制作收尸程序,父进程给子进程收尸
 pid_t pid=fork();//开展子进程 
 if(pid==0){
  //子进程的操作
  printf("我是子进程1  我的PID号为:%d\n",getpid());
  sleep(50);
  exit(100);//让子进程死亡,完成收尸,让操作停留在这里
 }
 pid_t pid2=fork();
 if(pid2==0){
  //子进程的操作
  printf("我是子进程2  我的PID号为:%d\n",getpid());
  printf("老二当前的组号为:%d\n",getpgid(pid2));
  printf("我!是!二!五!仔!\n");
  setpgid(pid2,pid2);//老二单独成组
  printf("老二叛变后的组号为:%d\n",getpgid(pid2));
  sleep(50);
  exit(2);//让子进程死亡,完成收尸,让操作停留在这里
 }
 pid_t pid3=fork();
 if(pid3==0){
  //子进程的操作
  printf("我是子进程3  我的PID号为:%d\n",getpid());
  sleep(50);
  exit(3);//让子进程死亡,完成收尸,让操作停留在这里
 }
 //父进程的操作
 //sleep(3);
 int wstatus,ret;
 //ret=waitpid(pid2,&wstatus,0);//给特定子进程收尸
 
 
 //给和父进程同一进程组下的子进程收尸
 /*while(1){
 ret=waitpid(0,&wstatus,0);
 if(ret==-1){
  break;
 }
 printf("被收尸的子进程是:%d\n",ret);
 }*/
 
 
 
 //给任意子进程收尸,无论同不同组
 /*while(1){
 ret=waitpid(-1,&wstatus,0);
 if(ret==-1){
  break;
 }
 printf("被收尸的子进程是:%d\n",ret);
 }*/
 
 
 
 //给进程组|pid|下的子进程收尸
 /*sleep(4);
 while(1){
 ret=waitpid(-pid2,&wstatus,0);
 if(ret==-1){
  break;
  }
 printf("被收尸的子进程是:%d\n",ret);
 }*/
 
 
 //死因追查
 sleep(2);
 waitpid(-1,&wstatus,WUNTRACED);
 if(WIFEXITED(wstatus)){//子进程是否正常死亡?
  printf("死亡原因:正常死亡,死亡状态为:%d\n",WEXITSTATUS(wstatus));
 }
 if(WIFSIGNALED(wstatus)){//子进程是否被信号停止或杀死
  printf("死亡原因:被信号%d杀死\n",WTERMSIG(wstatus));
 }
 if(WIFSTOPPED(wstatus)){//子进程是否被信号暂停
  printf("死亡原因:被信号%d暂停\n",WSTOPSIG(wstatus));
 }

 return 0;
}
```