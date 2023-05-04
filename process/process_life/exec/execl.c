// execl.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	printf("Current PID:%d\n", getpid());

	int ret = execl("./new", "./new", NULL);
	// 第一个./new--->在exec.c的执行目录下寻找一个名为new的可执行文件
	// 第二个./new--->执行 名为  new 的可执行文件，是替换后进程main函数的第一个参数
	// NULL 表示后面没有参数了，比如要传入一个参数arg1，execl("./new","./new",arg1,NULL),相当于参数列表停止标志。

	printf("被替换后不会打印这一行");

	return 0;
}
