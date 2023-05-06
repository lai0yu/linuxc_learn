# Linuxc网络应用层项目--类QQ

组员：赖林宇 罗炽龙 梁锦涛 粟磊

## 数据交流结构体

用json 进行打包解包

1. 通用数据

```c
struct data{
  int code,
  char msg[256];
  char data[1024];
}
```

客户端和服务器都要实现拆包解包

code 表示状态，msg表示拆包动作，如何拆包data

2.用户数据包  

```c
struct user_data{
  char username[128];
  char password[128];
}
```


## 客户端

### 登录界面

1. 界面函数原型：`void login_ui(void)`
2. 登录功能函数原型：`int login(const char* username, const char* password)`
3. 注册功能原型：`int register(const char* username, const char* password)`
4. 退出功能：直接调用exit
### 主界面

函数原型: `void main_ui(void)`


## 服务器