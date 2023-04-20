app : main.o link_stack.o
	gcc main.o link_stack.o -o app -Wall -O0

main.o: main.c link_stack.h
	gcc -c main.c -o main.o  -Wall -O0

link_stack.o : link_stack.c link_stack.h
	gcc -c link_stack.c -o link_stack.o -Wall -O0

