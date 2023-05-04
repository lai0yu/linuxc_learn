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
void* recv_work(void* arg){
	char buf[512];
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

	listen(serv_sock,512);
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr,&client_addr_len);
	printf("Client %d has connected\n",client_sock);

	pthread_t recv_thread;
	pthread_create(&recv_thread, NULL, recv_work,&client_sock);
	pthread_detach(recv_thread);

	char buf[512];
	while (1) {
		bzero(buf, sizeof(buf));
		scanf("%s",buf);
		send(serv_sock, buf, strlen(buf), 0);
	}
	pthread_cancel(recv_thread);
	close(serv_sock);
	close(client_sock);
	return 0;
}

