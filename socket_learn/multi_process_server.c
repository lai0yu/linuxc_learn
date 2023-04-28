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
static struct sockaddr_in* client_addrs[20] = {NULL};
static unsigned int client_addr_sizes[20] = {0};
static int client_socks[20] = {-1};
void* recv_work(void* arg){
	char buf[40];
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
	for (i = 0; i < 20; i++) {
		client_addrs[i] = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
		client_addr_sizes[i] = sizeof(*client_addrs[i]);
		client_socks[i] =	accept(serv_sock,(struct sockaddr*) client_addrs[i], &client_addr_sizes[i]);

		if (client_socks[i] > 0) {
			printf("A new client %s:%d has connected!\n",inet_ntoa((*client_addrs[i]).sin_addr), ntohs((*client_addrs[i]).sin_port));
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
	int self_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in self_addr;
	self_addr.sin_family = AF_INET;
	self_addr.sin_port = htons(atoi(argv[2]));
	self_addr.sin_addr.s_addr = inet_addr(argv[1]);

	int bind_ret = bind(self_sock,(struct sockaddr*) &self_addr, sizeof(self_addr));
	if (bind_ret != 0) {
		perror("bind failed");
		return -1;
	}

	listen(self_sock, 20);
	pthread_t accept_thread;
	pthread_create(&accept_thread, NULL, accept_work, &self_sock);
	pthread_detach(accept_thread);
    
	char buf[40];
	int i;
	while (1) {
		bzero(buf, sizeof(buf));
		scanf("%s",buf);
		for (i = 0; i < 20; i++) {
			if(client_socks[i] < 0){
				break;
			}
			send(client_socks[i],buf,sizeof(buf),0);
		}	
	}
}
