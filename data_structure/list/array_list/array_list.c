#include "array_list.h"

array_list* alist_init(){
	array_list* list = (array_list*)malloc(sizeof(array_list));
	list->array = (int*)(malloc(sizeof(int) * N));
	list->count = 0;
	list->capacity = N;
	return list;
}

int alist_resize(array_list* list, int capacity){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	list->array = (int*)realloc(list->array,sizeof(int) * capacity);
	list->capacity = capacity;
	return 0;
}

int alist_destroy(array_list* list){
	if(list == NULL){
		printf("NULL LIST");
		return -1;
	}
	free(list->array);
	list->array = NULL;
	free(list);
	return 0;
}

void alist_print(array_list* list){
	int i;
	for(i = 0; i < list->count; i++){
		printf("%d\t", list->array[i]);
	}
	printf("\n");
}

int alist_find_by_data(array_list* list, int data){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	int i;
	for(i = 0;i < list->count; i++){
		if(data == list->array[i]){
			return i;
		}
	}
	return -1;
}

int alist_empty(array_list* list){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	if(list->capacity != N){
		int resize_ret = alist_resize(list,N);
		if(resize_ret != 0){
			printf("RESIZE FAILED\n");
			return -1;
		}
	}
	list->count = 0;
	return 0;
}

int alist_add(array_list* list, int data){
	if(list == NULL){	
		printf("NULL LIST\n");
		return -1;
	}
	if(list->count == list->capacity){
		int resize_ret = alist_resize(list,list->capacity * 1.5);
		if(resize_ret != 0){
			printf("RESIZE FAILED");
			return -1;
		}
	}
	list->array[list->count] = data;
	list->count++;
	return 0;
	
}

int alist_add_at(array_list* list, int index, int data){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	if(index < 0 || index > list->count){
		printf("GIVEN INDEX OUT OF DATA\n");
		return -1;
	}
	if(list->count == list->capacity){
		int resize_ret = alist_resize(list, list->capacity * 1.5);
		if(resize_ret != 0){
			printf("RESIZE FAILED\n");
			return -1;
		}
	}
	int i; 
	for(i = list->count; i > index; i--){
		list->array[i] = list->array[i-1];
	}
	list->array[index] = data;
	list->count++;
	return 0;
}

int alist_del(array_list* list, int data){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	int i,j;
	for(i = 0; i < list->count; i++){
		if(list->array[i] == data){
			for(j = i; j < list->count - 1; j++){
				list->array[j] = list->array[j+1];
			}
			list->count--;
		}
	}
	return 0;
}
int alist_del_at(array_list* list, int index){
	if(list == NULL){
		printf("NULL LIST\n");
		return -1;
	}
	if(index < 0 || index >= list->count){
		printf("GIVEN INDEX OUT OF DATA\n");
		return -1;
	}

	int i;
	for(i = index; i < list->count-1; i++){
		list->array[i] = list->array[i+1];
	}
	list->count--;
	return 0;
}
