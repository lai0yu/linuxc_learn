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
	char send_buf[40],recv_buf[40];
	int send_ret = -1,recv_ret = -1;
	printf("wait message from client\n");
	while (1) {
		bzero(recv_buf, sizeof(recv_buf));
		recv_ret = recv(cli_sock, recv_buf, sizeof(recv_buf), 0);
		if (recv >=0) {
		
			printf("has recv message:%s from client:%d\n",recv_buf,cli_sock);
			printf("now need send message to client,please input:\n");
			bzero(send_buf, sizeof(send_buf));
			scanf("%s",send_buf);
			send_ret = send(cli_sock, send_buf, sizeof(send_buf), 0);
			if (send_ret >=0) {
				printf("send message to client:%d successfully\n",cli_sock);
				printf("now wait client message\n");
			}
		}
	}
	return 0;
}

