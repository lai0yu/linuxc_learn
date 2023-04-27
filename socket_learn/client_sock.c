#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
	if (argc < 3) {
		printf("Usage:%s <IP> <Port>\n",argv[0]);
		return -1;
	}
	int cli_sock = socket(AF_INET, SOCK_STREAM,IPPROTO_IP);

	struct sockaddr_in serv_sock_addr;
	serv_sock_addr.sin_family = AF_INET;
	serv_sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_sock_addr.sin_port = htons(atoi(argv[2]));
	int connect_ret =connect(cli_sock, (struct sockaddr*)&serv_sock_addr, sizeof(serv_sock_addr));
	if(connect_ret < 0){
		perror("connect error");
		return -1;
	}
	printf("connect success");
	char send_buf[40], recv_buf[40]; 
	int send_ret =1,recv_ret = -1;
	printf("now should send message to server, please input:\n");
	while (1) {
		bzero(send_buf, sizeof(send_buf));
		scanf("%s",send_buf);
		send_ret = send(cli_sock, send_buf, strlen(send_buf), 0);
		if (send_ret >= 0) {
			printf("send message:%s to server successfully!\n",send_buf);
			printf("now wait server response...\n");
			bzero(recv_buf, sizeof(recv_buf));
			recv_ret = recv(cli_sock, recv_buf, sizeof(recv_buf),0);
			if (recv_ret >=0) {
				printf("has recv server response message:%s\n",recv_buf);
				printf("now should send message to server, please input:\n");
			}
		}
	}
	return 0;
}
