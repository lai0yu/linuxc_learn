// array_json.c
#include <json/json.h>
#include <stdio.h>
#include <string.h>

struct user {
  int id;
  char name[20];
  char password[20];
};

int main(void) {
  struct user user0 = {0, "lai0yu", "123"};
  struct user user1 = {1, "tony", "1234"};
  struct user user2 = {2, "nancy", "12345"};
  struct user user3 = {3, "jack", "123456"};
  struct user user4 = {4, "bob", "1234567"};

  struct user users[5] = {
      user0,
      user1,
      user2,
      user3,
      user4,
  };

  struct json_object *object_arr = json_object_new_array();

  int i;

  struct json_object *object;
  struct json_object *object_id;
  struct json_object *object_name;
  struct json_object *object_password;

  for (i = 0; i < 5; i++) {
    object = json_object_new_object();
    object_id = json_object_new_int(users[i].id);
    object_name = json_object_new_string(users[i].name);
    object_password = json_object_new_string(users[i].password);

    json_object_object_add(object, "id", object_id);
    json_object_object_add(object, "name", object_name);
    json_object_object_add(object, "password", object_password);

    json_object_array_add(object_arr, object);
  }

  const char *p = json_object_to_json_string(object_arr);
  printf("%s\n", p);

  // 1>将字符串转化为数组对象
  struct json_object *objects_arr = json_tokener_parse(p);

  // 2>获取数组对象中 数据的个数
  int len = json_object_array_length(objects_arr);

  // 3>解包操作不需要一个数据写一条，而是交给循环
  // 循环前先指定名称
  int ii;                            // 循环的中间条件
  struct json_object *objects;       // 大对象
  struct json_object *obj_idstr;     // id 的json小对象名称
  struct json_object *obj_namestr;   // name的json小对象名称
  struct json_object *obj_passwdstr; // passwd 的json小对象名称

  for (ii = 0; ii < len; ii++) {
    // 1>从数组对象中获取大对象
    objects = json_object_array_get_idx(objects_arr, ii);

    // 2>通过标签，从大对象中获取json小对象
    obj_idstr = json_object_object_get(objects, "id");
    obj_namestr = json_object_object_get(objects, "name");
    obj_passwdstr = json_object_object_get(objects, "password");

    // 3>解析小包，并打印
    printf("id:%d ", json_object_get_int(obj_idstr));
    printf("name:%s ", json_object_get_string(obj_namestr));
    printf("password:%s ", json_object_get_string(obj_passwdstr));
    printf("\n");
  }

  return 0;
}