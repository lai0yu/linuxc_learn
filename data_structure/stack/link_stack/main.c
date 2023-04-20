#include "link_stack.h"

void push_sample_data(link_stack stack){
	int i;
	for(i = 0; i < 10; i++){
		lstack_push(stack,i*10);
	}
	printf("Init the List Stack finished!\n");
	lstack_print(stack);
}


void test_push_pop(link_stack stack){
    int input_ret,push_ret,pop_ret,input_data,pop_data;
    while(1){
    	input_ret = scanf("%d", &input_data);
        if(input_ret == 0){
            printf("Input illegal! Stop!\n");
            return;
        }
        if(input_data > 0){
            push_ret = lstack_push(stack,input_data);
        	if(push_ret == 0){
				printf("Has pushed data:%d into the List Stack!\n", input_data);
			}
			lstack_print(stack);
        }else if(input_data < 0){
            pop_ret = lstack_pop(stack,&pop_data);
        	if(pop_ret == 0){
				printf("Has poped data:%d from the List Stack\n",pop_data);
			}
			lstack_print(stack);
        }else{
            printf("Stoped Input!\n");
			return;
		}
    }
}

int main(void){
	link_stack stack = lstack_init();
	push_sample_data(stack);
	test_push_pop(stack);
	lstack_empty(stack);
	lstack_print(stack);
	lstack_destroy(stack);
	return 0;
}
