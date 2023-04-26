#ifndef	__HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef struct{
	int* data;
	int count;
	int capacity;
}hash_table

extern hash_table hstable_init();
extern int hstable_hash(hash_table* hstable, int key);
extern int hstable_add(hash_table* hstable, int data);
extern void hstable_print(hash_table* hstable);
extern void search(hash_table* hstable, int key, int *addr);
#endif


