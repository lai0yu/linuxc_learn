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
    printf("Usage:%s <ip> <port>\n", argv[0]);
    return -1;
  }
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  int on = 1;

  setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
  struct sockaddr_in bd_addr;
  bd_addr.sin_family = AF_INET;
  bd_addr.sin_port = htons(atoi(argv[2]));
  bd_addr.sin_addr.s_addr = inet_addr(argv[1]);

  if (bind(sockfd, (struct sockaddr*)&bd_addr, sizeof(bd_addr))) {
    perror("bind error");
    return -1;
  }
  char buf[40];
  int bd_addr_size = sizeof(bd_addr);
  while (1) {
    bzero(buf, sizeof(buf));
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&bd_addr,
             &bd_addr_size);
    printf("%s\n", buf);
  }
  return 0;
}
