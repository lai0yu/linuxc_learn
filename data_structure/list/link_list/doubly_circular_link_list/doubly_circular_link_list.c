#include "doubly_circular_link_list.h"

flight_data* create_data(
    char* number, 
    char* staddress,   
    char* arraddress,  
    char* DATE,   
    char* TYPE,  
    int stime,   
    int atime,   
    int value){
	flight_data* fdata = (flight_data*)malloc(sizeof(flight_data));
	fdata->number = number;
	fdata->staddress = staddress;
	fdata->arraddress = arraddress;
	fdata->DATE = DATE;
	fdata->TYPE = TYPE;
	fdata->stime = stime;
	fdata->atime = atime;
	fdata->value = value;
	return fdata;
}

fdclink_node* create_node(flight_data* data){
	fdclink_node* node = (fdclink_node*)malloc(sizeof(fdclink_node));
	node->data = data;
	return node;
}

fdclink_list fdcllist_init(){
	fdclink_node* head_node = (fdclink_node*)malloc(sizeof(fdclink_node));
	head_node->data = NULL;
	head_node->next = head_node;
	head_node->prev = head_node;
	return head_node;
}
int fdcllist_add(fdclink_node* prev, fdclink_node* next, fdclink_node* new_node){
	new_node->prev = prev;
	new_node->next = next;
	prev->next = new_node;
	next->prev = new_node;
	return 0;
}

int fdcllist_add_head(fdclink_list list, fdclink_node* new_node){
	fdcllist_add(list,list->next, new_node);
	return 0;
}
int fdcllist_add_tail(fdclink_list list, fdclink_node* new_node){
	fdcllist_add(list->prev,list,new_node);
	return 0;
}
int fdcllist_del(fdclink_node* prev, fdclink_node* next){
	free(prev->next->data);
	prev->next->data = NULL;
	free(prev->next);
	prev->next = next;
	next->prev = prev;
	return 0;
}
int fdcllist_del_head(fdclink_list list){
	fdcllist_del(list,list->next->next);
	return 0;
}
int fdcllist_del_tail(fdclink_list list){
	fdcllist_del(list->prev->prev,list);
	return 0;
}
fdclink_list fdcllist_find_by_number(fdclink_list list, char* number){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(strcmp(cursor->data->number,number) == 0){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
fdclink_list fdcllist_find_by_sta(fdclink_list list, char* staddress){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(strcmp(cursor->data->staddress,staddress) == 0){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}

fdclink_list fdcllist_find_by_arr(fdclink_list list, char* arraddress){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(strcmp(cursor->data->arraddress,arraddress) == 0){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}

fdclink_list fdcllist_find_by_date(fdclink_list list, char* DATE){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(strcmp(cursor->data->DATE,DATE) == 0){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
fdclink_list fdcllist_find_by_type(fdclink_list list, char* TYPE){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(strcmp(cursor->data->TYPE,TYPE) == 0){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
fdclink_list fdcllist_find_by_stime(fdclink_list list, int stime){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(cursor->data->stime == stime){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
fdclink_list fdcllist_find_by_atime(fdclink_list list, int atime){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(cursor->data->atime == atime){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
fdclink_list fdcllist_find_by_value(fdclink_list list, int value){
	fdclink_node* cursor = list->next;
	fdclink_list new_list = fdcllist_init(); 
	while(cursor != list){
		if(cursor->data->value == value){
			flight_data* clone_data = create_data(cursor->data->number,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->TYPE,cursor->data->stime,cursor->data->atime,cursor->data->value);
			fdcllist_add_tail(new_list, create_node(clone_data));
		}
		cursor = cursor->next;
	}
	return new_list;
}
int fdcllist_update_node(fdclink_node* old_node, fdclink_node* new_node){
	return 0;
}

void fdcllist_print(fdclink_list list){
	fdclink_node* cursor = list->next;
	printf("|******************************************Begin****************************************|\n");
	printf("航班号\t机型\t价格\t起飞站\t终点站\t班期\t\t起飞小时\t到达小时\n");
	while(cursor != list){
		printf("-------------------------------------------------------------------------------------\n");
		printf("%s\t%s\t%d\t%s\t%s\t%s\t%d\t\t%d\n",cursor->data->number,cursor->data->TYPE,cursor->data->value,cursor->data->staddress,cursor->data->arraddress,cursor->data->DATE,cursor->data->stime,cursor->data->atime);
		cursor = cursor->next;
	}
	printf("|******************************************Over****************************************|\n");
}


void fdcllist_sort_by_stime(fdclink_list list){
	fdclink_node *cursor, *jcursor;
	jcursor = list->next;
	cursor = list->prev;
	flight_data* temp = NULL;
	while(cursor != list->next){
		jcursor = list->next;
		while(jcursor->next != cursor){
			if(jcursor->data->stime > jcursor->next->data->stime){
				temp = jcursor->data;
				jcursor->data = jcursor->next->data;
				jcursor->next->data = temp;
			}
			jcursor = jcursor->next;
		}
		cursor = cursor->prev;
	}
}


void fdcllist_sort_by_atime(fdclink_list list){
	fdclink_node *cursor, *jcursor;
	jcursor = list->next;
	cursor = list->prev;
	flight_data* temp = NULL;
	while(cursor != list->next){
		jcursor = list->next;
		while(jcursor->next != cursor){
			if(jcursor->data->atime > jcursor->next->data->atime){
				temp = jcursor->data;
				jcursor->data = jcursor->next->data;
				jcursor->next->data = temp;
			}
			jcursor = jcursor->next;
		}
		cursor = cursor->prev;
	}		
}

int fdcllist_empty(fdclink_list list){
	while(list->next != list){
		fdcllist_del_tail(list);
	}
	return 0;
}
int fdcllist_destroy(fdclink_list* list){
	fdcllist_empty(*list);
	free((*list)->data);
	(*list)->data = NULL;
	free(*list);
	*list = NULL;
	return 0;
}
