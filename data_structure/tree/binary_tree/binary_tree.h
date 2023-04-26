#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
typedef struct s_btree_node{
	int data;
	struct s_btree_node* left;
	struct s_btree_node* right;
}btree_node;

type struct{
	btree_node* root;
}tree;


#endif
