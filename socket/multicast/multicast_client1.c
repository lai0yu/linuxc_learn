#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
  if (argc < 4) {
    printf("Usage:%s, <Ip> <Self_Port> <Other_Port>\n", argv[0]);
    return -1;
  }

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("init sock error");
    return -1;
  }

  struct sockaddr_in self_addr;
  self_addr.sin_family = AF_INET;
  self_addr.sin_port = htons(atoi(argv[2]));
  self_addr.sin_addr.s_addr = inet_addr(argv[1]);

  int bind_ret = bind(sock, (struct sockaddr*)&self_addr, sizeof(self_addr));

  if (bind_ret != 0) {
    perror("bind failed");
    return -1;
  }

  struct sockaddr_in other_addr;
  other_addr.sin_family = AF_INET;
  other_addr.sin_port = htons(atoi(argv[3]));
  other_addr.sin_addr.s_addr = inet_addr(argv[1]);

  char buf[40];
  int len = sizeof(other_addr);
  while (1) {
    bzero(buf, sizeof(buf));
    recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, &len);
    printf("%s\n", buf);
  }
  return 0;
}
