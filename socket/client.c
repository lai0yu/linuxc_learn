// client.c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
void* recv_work(void* arg) {
  char buf[512];
  int recv_ret = -1;
  while (1) {
    bzero(buf, sizeof(buf));
    int recv_ret = recv(*(int*)(arg), buf, sizeof(buf), 0);
    if (recv_ret > 0) {
      printf("%s\n", buf);
    }
  }
}
int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage:%s <IP> <Port>\n", argv[0]);
    return -1;
  }
  int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

  struct sockaddr_in serv_sock_addr;
  serv_sock_addr.sin_family = AF_INET;
  serv_sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_sock_addr.sin_port = htons(atoi(argv[2]));
  int connect_ret = connect(serv_sock, (struct sockaddr*)&serv_sock_addr,
                            sizeof(serv_sock_addr));
  if (connect_ret < 0) {
    perror("connect error");
    return -1;
  }

  pthread_t recv_thread;
  pthread_create(&recv_thread, NULL, recv_work, &serv_sock);
  pthread_detach(recv_thread);

  char buf[512];
  while (1) {
    bzero(buf, sizeof(buf));
    scanf("%s", buf);
    send(serv_sock, buf, strlen(buf), 0);
  }
  pthread_cancel(recv_thread);
  close(serv_sock);
  return 0;
}
