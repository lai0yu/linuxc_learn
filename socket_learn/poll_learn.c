#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  char buf[40];
  struct pollfd fds[1];
  fds[0].fd = 0;
  fds[0].events = POLLIN; // 想要0号文件描述符触发读属性

  int ret;
  while (1)
  {
    ret = poll(fds, 1, -1);
    if (ret < 0)
    {
      perror("poll failed");
      return -1;
    }
    if (fds[0].revents == POLLIN)
    {
      bzero(buf, sizeof(buf));
      read(0, buf, sizeof(buf));
      printf("%s\n", buf);
      fds[0].revents = 0;
    }
  }
  return 0;
}