app:main.o doubly_circular_link_list.o
	gcc main.o doubly_circular_link_list.o -o app -Wall -O0
main.o : main.c doubly_circular_link_list.h
	gcc -c main.c -o main.o -Wall -O0
doubly_circular_link_list.o : doubly_circular_link_list.c doubly_circular_link_list.h
	gcc -c  doubly_circular_link_list.c -o doubly_circular_link_list.o -Wall -O0
