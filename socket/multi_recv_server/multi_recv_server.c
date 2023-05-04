// multi_recv_server.c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <ip> <port>\n", argv[0]);
    return -1;
  }

  int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htonl(atoi(argv[2]));

  bind(serv_sock, (struct sockaddr *)&serv_sock, sizeof(serv_addr));
  listen(serv_sock, 100);
  int client_socks[100] = {-1};
  struct sockaddr_in client_addrs[100];
  socklen_t client_addr_sizes[100] = {sizeof(client_addrs[0])};
  int clients_count = 0;
  while (1) {
    client_socks[clients_count] =
        accept(serv_sock, (struct sockaddr *)&client_addrs[clients_count],
               &client_addr_sizes[clients_count]);
    if (client_socks[clients_count] > 0) {
      clients_count++;
    }
  }

  return 0;
}
