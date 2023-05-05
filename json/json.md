# JSON

json是一种轻量级的数据交换格式 它基于 ECMAScript（European Computer Manufacturers Association, 欧洲计算机协会制定的js规范）的一个子集，采用完全独立于编程语言的文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率

[toc]

***

[代码仓库](https://github.com/lai0yu/linuxc_learn/tree/master/json)

## 安装

[文件下载](https://github.com/lai0yu/linuxc_learn/blob/master/json/json-c-0.9.tar.gz)

```shell
$ sudo tar xvzf json-c-0.9.tar.gz
$ cd json-c-0.9
$ sudo ./configure --prefix=/usr/local
$ sudo make
$ sudo make install
```

## 使用

从外部安装的json库，系统不一定认识，需要配置可执行文件

1. 打开配置文件

    ```shell
    sudo vim /etc/ld.so.conf
    ```

2. 在新的一行中添加`/usr/lib`  
3. 保存退出后执行

    ```shell
    sudo ldconfig
    ```

Demo1
```c
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
```

编译并运行  
![json_pack](https://pic2.imgdb.cn/item/6454f26c0d2dde57776fb03f.jpg)

Demo2 数组数据

```c
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
```

编译并运行  
![array_json](https://pic2.imgdb.cn/item/6454f7800d2dde57777718a7.jpg)
