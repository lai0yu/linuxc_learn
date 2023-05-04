// exit.c
#include <stdio.h>
#include <stdlib.h>
void test() {
  printf("88技师为您服务\n");
  exit(1);
}
int main() {
  test();
  printf("99号技师为您服务\n");
  return 0;
}
