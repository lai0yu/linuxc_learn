#ifndef __CQQ_SERVER_DATA_H__
#define __CQQ_SERVER_DATA_H__

struct data {
  int code;
  char msg[256];
  char data[1024];
};

struct user_data {
  char username[128];
  char password[128];
};

extern struct data parse_json(char *json_str);
extern char *pack_json(struct data);

#endif