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