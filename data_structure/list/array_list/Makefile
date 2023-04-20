app : main.o array_list.o
	gcc main.o array_list.o -o app -Wall -O0
main.o : main.c array_list.h
	gcc -c main.c -o main.o -Wall -O0
array_list.o : array_list.c array_list.h
	gcc -c array_list.c -o array_list.o -Wall -O0
