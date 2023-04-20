#ifndef __DOUBLY_CIRCULAR_LINK_LIST_H__
#define __DOUBLY_CIRCULAR_LINK_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_flight_data       //航班信息数据结构
{   
    char* number;    //航班号    
    char* staddress;   //起点站    
    char* arraddress;   //终点站    
    char* DATE;       //班期    
    char* TYPE;       //机型    
    int stime;          //起飞时间    
    int atime;          //到达时间    
    int value;           //票价     
}flight_data;

typedef struct s_fdclink_node{
	flight_data* data;
	struct s_fdclink_node *prev;
	struct s_fdclink_node *next;
}fdclink_node, *fdclink_list;

extern flight_data* create_data(char* number, char* staddress, char* arraddress, char* DATE, char* TYPE, int stime,int atime, int value);
extern fdclink_node* create_node(flight_data* data);
extern fdclink_list fdcllist_init();
extern int fdcllist_add(fdclink_node* prev, fdclink_node* next, fdclink_node* new_node);
extern int fdcllist_add_head(fdclink_list list, fdclink_node* new_node);
extern int fdcllist_add_tail(fdclink_list list, fdclink_node* new_node);
extern int fdcllist_del(fdclink_node* prev, fdclink_node* next);
extern int fdcllist_del_head(fdclink_list list);
extern int fdcllist_del_tail(fdclink_list list);
extern fdclink_list fdcllist_find_by_number(fdclink_list list, char* number);
extern fdclink_list fdcllist_find_by_sta(fdclink_list list, char* staddress);
extern fdclink_list fdcllist_find_by_arr(fdclink_list list, char* arraddress);
extern fdclink_list fdcllist_find_by_date(fdclink_list list, char* DATE);
extern fdclink_list fdcllist_find_by_type(fdclink_list list, char* TYPE);
extern fdclink_list fdcllist_find_by_stime(fdclink_list list, int stime);
extern fdclink_list fdcllist_find_by_atime(fdclink_list list, int atime);
extern fdclink_list fdcllist_find_by_value(fdclink_list list, int value);
extern int fdcllist_update_node(fdclink_node* old_node, fdclink_node* new_node);
extern void fdcllist_print(fdclink_list list);
extern void fdcllist_sort_by_stime(fdclink_list list);
extern void fdcllist_sort_by_atime(fdclink_list list);
extern int fdcllist_empty(fdclink_list list);
extern int fdcllist_destroy(fdclink_list *list);
#endif
