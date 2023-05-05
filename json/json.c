// json.c
#include <json/json.h>
#include <stdio.h>
#include <string.h>
struct user {
  int id;
  char name[20];
  char password[20];
};

int main(void) {
  // json装包
  struct user user_send = {1, "lai0yu", "123"};

  struct json_object *obj_id = json_object_new_int(user_send.id);
  struct json_object *obj_name = json_object_new_string(user_send.name);
  struct json_object *obj_password = json_object_new_string(user_send.password);

  struct json_object *obj = json_object_new_object();

  json_object_object_add(obj, "name", obj_id);
  json_object_object_add(obj, "name", obj_name);
  json_object_object_add(obj, "password", obj_password);

  const char *p = json_object_to_json_string(obj);

  printf("%s\n", p);

  // json解包
  struct user user_recv;

  struct json_object *objs = json_tokener_parse(p);

  struct json_object *obj_idstr = json_object_object_get(objs, "id");
  struct json_object *obj_namestr = json_object_object_get(objs, "name");
  struct json_object *obj_passwordstr = json_object_object_get(objs, "password");

  user_recv.id = json_object_get_int(obj_idstr);
  strcpy(user_recv.name, json_object_get_string(obj_namestr));
  strcpy(user_recv.password, json_object_get_string(obj_passwordstr));

  printf("id:%d, name:%s, password:%s", user_recv.id, user_recv.name, user_recv.password);
  return 0;
}
