#ifndef __LINK_STACK_H__
#define __LINK_STACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{
	int data;
    struct s_node* next;
}stack_node,*link_stack;

extern link_stack lstack_init();
extern void lstack_print(link_stack stack);
extern int lstack_push(link_stack stack, int data);
extern int lstack_pop(link_stack stack, int* recv);
extern int lstack_empty(link_stack stack);
extern int lstack_destroy(link_stack stack);

#endif
