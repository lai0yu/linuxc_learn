# 本地数据持久化--sqlite3

sqlite可以说是本地数据持久化应用最广泛的解决方案了,不同于MySQL，MSSQLServer等数据库程序，sqlite只是一个文件，不需要单独的进程去运行它，只需要在自己的程序内嵌入并使用它。

* sqlite是非常小的，轻量级的数据库，完全配置时小于400KiB，省略可选功能配置时小于250KiB
* sqlite不需要任何外部的依赖
* sqlite可在UINX（Linux，Max OS-X,Android，iOS）和Windows（Win32，WinCE，WinRT）中运行
* sqlite使用ANSI-C编写的，并提供了简单和易于使用的API
* sqlite支持SQL92（SQL2）标准的大多数查询语言的功能
* sqlite实现了事务性，而且是完全兼容ACID的，允许从多个进程或线程安全访问

[toc]  
***
[代码仓库](https://github.com/lai0yu/linuxc_learn/tree/master/sqlite3)

## 安装

有一些系统会自带sqlite，先看本地有没有已经安装好的, 如果出现以下类似的结果就说明已经有安装好的

```shell
$ sqlite3
SQLite version 3.7.15.2 2013-01-09 11:53:05
Enter ".help" for instructions
Enter SQL statements terminated with a ";"
sqlite>
```

如果没有就去[sqlite下载页面](https://www.sqlite.org/download.html)源代码区下载 sqlite-autoconf-*.tar.gz

或者直接[从代码仓库下载](https://github.com/lai0yu/linuxc_learn/tree/master/sqlite3)

```shell
$ sudo tar xvzf sqlite-autoconf-3240000.tar.gz
$ cd sqlite-autoconf-3240000
$ sudo ./configure --prefix=/usr/local
$ sudo make
$ sudo make install
```

## 命令行使用

```shell
sqlite3 #进入sqlite3
.databases   #列出数据库文件名     ***
.tables ?PATTERN?  #列出?PATTERN?匹配的表名   ***
.import FILE TABLE #将文件中的数据导入的文件中
.dump ?TABLE?   #生成形成数据库表的SQL脚本
.output FILENAME  #将输出导入到指定的文件中
.output stdout   #将输出打印到屏幕    *** 
.mode MODE ?TABLE?     #设置数据输出模式(csv,html,tcl… 
.nullvalue STRING #用指定的串代替输出的NULL串
.read FILENAME  #执行指定文件中的SQL语句   ***
.schema ?TABLE? #打印创建数据库表的SQL语句    ***
.separator STRING  #用指定的字符串代替字段分隔符
.show    #打印所有SQLite环境变量的设置
.quit    #退出命令行接口      ***
```

### 表的增删查改

```shell
create table if not exists users(id int, name char[20]);
drop table users;
alter table users add column passwd char[20];
.tables users
```

### 数据的增删查改

```sql
insert into users values(1,"吴亦凡","123");
insert into users values(2,"李易峰","1234");
insert into users values(3,"罗志祥","12345");
delete from users where id==1;
select * from users;
select * from users where name=="罗志祥";
update users set name=李云迪, where id==3;
```

## 数据库API

1. 打开数据库

```c
int sqlite3_open(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);

```

1. 执行sql语句
  
```c
int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);
```

demo
```c
// sqlite3.c
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

int sql_callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  fprintf(stderr, "%s: ", (const char *)data);
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char *argv[]) {

  // 打开数据库，如果没有就会创建
  sqlite3 *ppdb;
  int ret = sqlite3_open("test.db", &ppdb);
  if (ret != SQLITE_OK) {
    perror("open sqlite database failed");
    return -1;
  }

  char *errormsg = 0;

  // 创建表
  char sql[100] =
      "create table if not exists user(id int, name char[20],password char[20]);";

  ret = sqlite3_exec(ppdb, sql, NULL, NULL, &errormsg);
  if (ret != SQLITE_OK) {
    printf("sql exec error:%s\n, error message:%s\n", sql, errormsg);
    return -1;
  }

  // 插入数据
  bzero(sql, sizeof(sql));
  strcpy(sql, "insert into user values(1,'吴亦凡', 123);");
  ret = sqlite3_exec(ppdb, sql, NULL, NULL, &errormsg);
  if (ret != SQLITE_OK) {
    printf("sql exec error:%s\n, error message:%s\n", sql, errormsg);
    return -1;
  }

  // 查询数据
  bzero(sql, sizeof(sql));
  strcpy(sql, "select * from user;");
  const char *data = "Callback function called";
  ret = sqlite3_exec(ppdb, sql, sql_callback, (void *)data, &errormsg);
  if (ret != SQLITE_OK) {
    printf("sql exec error:%s\n, error message:%s\n", sql, errormsg);
    return -1;
  }

  return 0;
}

```

编译并运行
![sqlite3](https://pic2.imgdb.cn/item/6454b5e40d2dde57771d2949.jpg)
