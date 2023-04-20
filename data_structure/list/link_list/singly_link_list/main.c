#include "singly_link_list.h"


void test_add(slink_list list){
	while(1){
		int d;
		scanf("%d",&d);
		if(d>0){
			sllist_add_head(list,d);	
			sllist_print(list);
		}else if(d < 0){
			sllist_add_tail(list,d);
			sllist_print(list);
		}else{
			break;
		}

	}
}

void test_del(slink_list list){
	while(1){
		int d;
		scanf("%d",&d);
		if(d>0){
			sllist_del_head(list);	
			sllist_print(list);
		}else if(d < 0){
			sllist_del_tail(list);
			sllist_print(list);
		}else{
			break;
		}

	}
}

int main(void){
	slink_list list = sllist_init();
	int i;
	for(i = 0; i < 10; i++){
		sllist_add_tail(list, i*10);
	}
	sllist_print(list);
	test_add(list);
	test_del(list);
}
