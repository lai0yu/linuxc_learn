#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Usage:%s <ip> port\n", argv[0]);
  }
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  int on = 1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
  struct sockaddr_in sock_addr;
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(atoi(argv[2]));
  sock_addr.sin_addr.s_addr = inet_addr(argv[1]);

  char buf[40];
  while (1) {
    bzero(buf, sizeof(buf));
    scanf("%s", buf);
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&sock_addr,
           sizeof(sock_addr));
  }
  return 0;
}
