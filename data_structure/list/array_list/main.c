#include "array_list.h"

int main(void){
	array_list* list = alist_init();
	int i = 0;
	for(i = 0; i < 9; i++){
		alist_add(list,i*10);
	}
	alist_print(list);
	alist_del(list,50);
	alist_print(list);
	alist_del_at(list,3);
	alist_print(list);
	alist_add(list,90);
	alist_print(list);
	alist_add_at(list,3,89);
	alist_print(list);
	printf("%d",alist_find_by_data(list, 60));
	alist_empty(list);
	alist_print(list);
	return 0;
}
