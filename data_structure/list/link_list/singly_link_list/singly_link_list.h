#ifndef __SINGLY_LINK_LIST_H__
#define __SINGLY_LINK_LIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct s_slink_node{
	int data;
	struct s_slink_node* next;
}slink_node, *slink_list;

extern slink_list sllist_init();
extern void sllist_print(slink_list list);
extern int sllist_add_head(slink_list list, slink_node* node);
extern int sllist_add_tail(slink_list list, slink_node* node);
extern int sllist_del_head(slink_list list);
extern int sllist_del_tail(slink_list list);
extern slink_node* sllist_find_by_data(slink_list, int data);
extern int sllist_update(slink_list list, slink_node* new_node, slink_node* old_node);
extern int sllist_empty(slink_list list);
extern int sllist_destroy(slink_list list);
#endif
