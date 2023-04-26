#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
int main(void){
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(54321);
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
		perror("bind error");
		return -1;
	}	

	listen(serv_sock,40);
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_len = sizeof(cli_addr);
	int cli_sock = accept(serv_sock, (struct sockaddr*)&cli_addr,&cli_addr_len);
	printf("Client %d has connected\n",cli_sock);
	char str[] = "Hello";


	write(cli_sock, str, sizeof(str));
	char buf[40];
	while (1) {
		bzero(buf, sizeof(buf));
		recv(cli_sock, buf, sizeof(buf), 0);
		printf("Server Has Recv:%s\n",buf);
	}


	return 0;
}
