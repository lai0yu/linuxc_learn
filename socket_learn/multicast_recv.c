#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Usage:%s <ip> <port>\n", argv[0]);
  }
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  return 0;
}