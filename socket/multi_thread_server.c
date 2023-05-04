#include <pthread.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#define MAX_CONNECT 100
struct sockaddr_in* client_addrs[MAX_CONNECT] = {NULL};
unsigned int client_addr_sizes[MAX_CONNECT] = {0};
int client_socks[MAX_CONNECT] = {-1};
int client_count = 0;
void* recv_work(void* arg){
	char buf[512];
	int recv_ret = -1;
	while (1) {
		bzero(buf, sizeof(buf));
		recv_ret = recv(*(int*)arg, buf, sizeof(buf), 0);
		if(recv_ret > 0){
			printf("message from %d:%s\n",*(int*)arg, buf);
		}
	}
}
void* accept_work(void* arg){
	int serv_sock = *(int*)arg;	

	int i;
	for (i = 0; i < MAX_CONNECT; i++) {
		client_addrs[i] = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
		client_addr_sizes[i] = sizeof(*client_addrs[i]);
		client_socks[i] =	accept(serv_sock,(struct sockaddr*) client_addrs[i], &client_addr_sizes[i]);

		if (client_socks[i] > 0) {
			printf("A new client %s:%d has connected!\n",inet_ntoa((*client_addrs[i]).sin_addr), ntohs((*client_addrs[i]).sin_port));
			client_count++;
			pthread_t recv_thread;
			pthread_create(&recv_thread, NULL, recv_work,(void*)&client_socks[i]);
			pthread_detach(recv_thread);
		}
	}
	return NULL;
}
int main(int argc, char* argv[]){

	if(argc < 3){
		printf("Usage:%s <IP> <Port>\n",argv[0]);
		return -1;
	}
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in self_addr;
	self_addr.sin_family = AF_INET;
	self_addr.sin_port = htons(atoi(argv[2]));
	self_addr.sin_addr.s_addr = inet_addr(argv[1]);

	int bind_ret = bind(serv_sock,(struct sockaddr*) &self_addr, sizeof(self_addr));
	if (bind_ret != 0) {
		perror("bind failed");
		return -1;
	}

	listen(serv_sock, MAX_CONNECT);
	pthread_t accept_thread;
	pthread_create(&accept_thread, NULL, accept_work, &serv_sock);
	pthread_detach(accept_thread);
    
	char buf[512];
	int i;
	while (1) {
		bzero(buf, sizeof(buf));
		scanf("%s",buf);
		for (i = 0; i < MAX_CONNECT; i++) {
			if(client_socks[i] < 0){
				break;
			}
			send(client_socks[i],buf,strlen(buf),0);
		}	
	}
	pthread_cancel(accept_thread);
	close(serv_sock);
	for (i = 0; i < MAX_CONNECT; i++) {
		if(client_socks[i] > 0){
			close(client_socks[i]);
			client_socks[i] = -1;
		}
		if (client_addr_sizes[i] !=0) {
			client_addr_sizes[i] = 0;
		}
		if(client_addrs[i] != NULL){
			free(client_addrs[i]);
			client_addrs[i] = NULL;
		}
	}
	client_count = 0;
	return 0;
}
