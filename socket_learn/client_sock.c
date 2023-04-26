#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(void){
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serv_sock_addr;

	serv_sock_addr.sin_family = AF_INET;
	serv_sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_sock_addr.sin_port = htons(54321);
	int connect_ret =connect(serv_sock, (struct sockaddr*)&serv_sock_addr, sizeof(serv_sock_addr));
	if(connect_ret < 0){
		perror("connect error");
		return -1;
	}
	printf("connect success");
	char str[40]; 
	read(serv_sock, str, sizeof(str));
	printf("Message from server:%s\n",str);
	while (1) {
		bzero(str, sizeof(str));
		scanf("%s",str);
		send(serv_sock, str, strlen(str), 0);
	}
	return 0;
}
