#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	printf("Current Pid:%d\n",getpid());

	int ret = execlp("ls","ls","a",NULL);
	//第一个ls  :在默认/bin  和 /usr/bin 寻找一个名为ls的命令
	//第二个ls  :执行ls 
	//第三个-l  :执行ls命令下 -l 选项,显示文件详细信息
	
	printf("被替换后不会再打印这一行\n");

	return 0;
}
