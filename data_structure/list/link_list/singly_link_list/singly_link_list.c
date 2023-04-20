#include "singly_link_list.h"

slink_list sllist_init(){
	slink_node* head = (slink_node*)malloc(sizeof(slink_node));
	head->next = NULL;
	return head;
}


void sllist_print(slink_list list){
	slink_node* cursor = list->next;
	printf("HEAD-->");
	while(cursor != NULL){
		printf("%d-->",cursor->data);
		cursor = cursor->next;
	}
	printf("NULL\n");
}

int sllist_add_tail(slink_list list, slink_node* node){
	slink_node* tail_node = list;
	while(tail_node->next != NULL){
		tail_node = tail_node->next;
	}
	tail_node->next = node;
	return 0;
}

int sllist_add_head(slink_list list, slink_node* node){	
	node->next = list->next;
	list->next = node;
	return 0;
}

int sllist_del_head(slink_list list){	
	slink_node* temp = list->next;
	list->next = list->next->next;
	temp->next = NULL;
	free(temp);
	temp = NULL;
	return 0;
}

int sllist_del_tail(slink_list list){	
	slink_node* tail_prev_node = list;
	while(tail_prev_node->next->next != NULL){
		tail_prev_node = tail_prev_node->next;
	}
	slink_node* temp = tail_prev_node->next;
	tail_prev_node->next = NULL;
	free(temp);
	temp = NULL;
	return 0;
}

int sllist_empty(slink_list list){
	while(list->next != NULL){
		sllist_del_head(list);
	}
	return 0;
}

slink_node* sllist_find_by_data(slink_list list, int data){	
	slink_node* cursor = list->next;
	printf("HEAD-->");
	while(cursor != NULL){
		if(cursor->data == data){
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

slink_node* sllist_find_prev_node(slink_list list, slink_node* node){
	slink_node *cursor = list->next;
	while(cursor != NULL && cursor->next != NULL){
		if(cursor->next == node){
			return cursor;
		}
		cursor = cursor->next;
	}
	return NULL;
}

int sllist_update(slink_node* new_node, slink_node* old_node){
	
}
