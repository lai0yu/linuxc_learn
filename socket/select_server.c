#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CONNECT 100
int client_socks[MAX_CONNECT] = {-1};
struct sockaddr_in* client_addrs[MAX_CONNECT] = {NULL};
unsigned int client_addr_sizes[MAX_CONNECT] = {0};
int current_client_count = 0;
fd_set fdset;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* accept_work(void* arg){
	pthread_mutex_lock(&mutex);
	int serv_sock = *(int*)arg;
	int i;
	for (i = 0; i < MAX_CONNECT; i++) {
		client_addrs[i] = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
		client_addr_sizes[i] = sizeof(*client_addrs[i]);
		client_socks[i] = accept(serv_sock,(struct sockaddr*) client_addrs[i], &client_addr_sizes[i]);

		if (client_socks[i] > 0) {
			printf("A new client %s:%d has connected!\n",inet_ntoa((*client_addrs[i]).sin_addr), ntohs((*client_addrs[i]).sin_port));
			current_client_count++;
		}
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}
void* send_work(void* arg){
	char s[40];
	int i;
	while (1) {
		bzero(s, sizeof(s));
		scanf("%s",s);
		for (i = 0; i < current_client_count; i++) {
			send(client_socks[i],s,sizeof(s),0);
		}
	}	
}
int main(int argc, char* argv[]){
	if (argc < 3) {
		printf("Usage:%s <ip> <port>\n",argv[0]);
		return -1;
	}

	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(serv_sock, MAX_CONNECT);

	pthread_t accept_thread;
	pthread_create(&accept_thread, NULL, accept_work, &serv_sock);
	pthread_detach(accept_thread);

	pthread_t send_thread;
	pthread_create(&send_thread,NULL,send_work,&serv_sock);
	pthread_detach(send_thread);
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	int i,j,select_ret, recv_ret;

	char recv_buf[512];

	while (1) {
		FD_ZERO(&fdset);
		FD_SET(serv_sock,&fdset);
		for (i = 0; i < current_client_count; i++) {
			if(client_socks[i] > 0){
				FD_SET(client_socks[i],&fdset);	
			}
		}		
		select_ret = select(MAX_CONNECT+1, &fdset, NULL, NULL, &tv);			
		if (select_ret < 0) {
			perror("select failed");
			break;
		}else if(select_ret == 0){
			continue;
		}else{
			for(int i = 0; i < current_client_count; i++){
				if(FD_ISSET(client_socks[i], &fdset)){
					bzero(recv_buf, sizeof(recv_buf));
					int recv_ret = recv(client_socks[i], recv_buf, sizeof(recv_buf), 0);
					if (recv_ret > 0) {
						printf("Message from client %s:%d==>%s\n",inet_ntoa(client_addrs[i]->sin_addr),ntohs(client_addrs[i]->sin_port),recv_buf);
					}
				}
			}
		}
	}
	pthread_cancel(accept_thread);
	pthread_cancel(send_thread);
	close(serv_sock);
	for(i = 0; i < MAX_CONNECT; i++){
		if(client_addrs[i] != NULL){
			free(client_addrs[i]);
			client_addrs[i] = NULL;
		}
		if(client_socks >=0){
			close(client_socks[i]);
		}
		client_addr_sizes[i] = 0;
	}
	return 0;
}
