#include "link_stack.h"

link_stack lstack_init(){
	stack_node* head = (stack_node*)malloc(sizeof(stack_node));
	head->next = NULL;
	return head;
}


void lstack_print(link_stack stack){
	if(stack->next == NULL){
   		printf("|===============|<--NULL STACK\n");
		return;
	}
	stack_node* cursor = stack->next;
	
    printf("|\t%d\t|<--top\n",cursor->data);	
    while(cursor->next != NULL){
    	cursor = cursor->next;
		printf("|\t%d\t|\n",cursor->data);
	}
   	printf("|===============|\n");
}

int lstack_push(link_stack stack,int data){
	stack_node *new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->data = data;
    new_node->next = stack->next;
    stack->next = new_node;
	return 0;
}

int lstack_pop(link_stack stack, int *recv){
	if(stack->next == NULL){
        printf("NULL STACK, POP INVALID\n");
		return -1;
	}
    stack_node *temp = stack->next;
	stack->next = temp->next;
	*recv = temp->data;
    temp->next = NULL;
    free(temp);
	return 0;
}

int lstack_empty(link_stack stack){
	int recv = 0;
	while(stack->next != NULL){
		lstack_pop(stack,&recv);
	}
	return 0;
}

int lstack_destroy(link_stack stack){
	lstack_empty(stack);
	free(stack);
	return 0;
}
