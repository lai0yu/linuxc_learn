app : main.o singly_link_list.o
	gcc main.o singly_link_list.o -o app -Wall -O0

main.o : main.c singly_link_list.h
	gcc -c main.c -o main.o -Wall -O0

singly_link_list.o : singly_link_list.c singly_link_list.h
	gcc -c singly_link_list.c -o singly_link_list.o -Wall -O0
