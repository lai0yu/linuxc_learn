// array_list.h
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define N 5

#include <stdio.h>
#include <stdlib.h>

typedef struct s_array_list {
    int* array;
    int count;
    int capacity;
} array_list;

extern array_list* alist_init();
extern void alist_print(array_list* list);
extern int alist_add(array_list* list, int data);
extern int alist_add_at(array_list* list, int index, int data);
extern int alist_del(array_list* list, int data);
extern int alist_del_at(array_list* list, int index);
extern int alist_empty(array_list* list);
extern int alist_find_by_data(array_list* list, int data);
extern int alist_update(array_list* list, int old_data, int new_data);
extern int alist_destroy(array_list* list);
#endif
